//#include "stdafx.h"
//#include "net_lib_private.h"
#include "platform.h"
#ifndef GAME_SERVER
#include "iconv.h"
#endif

#ifdef LINUX
	timeval start;
#else // windows
#include <mmsystem.h>
	#pragma comment(lib,"Winmm.lib")
#endif

bool g_enable_log = true;

void Sys_Init()
{
#ifdef LINUX
	start.tv_sec  = 0;
	start.tv_usec = 0;
	gettimeofday(&start, NULL);
#endif
}

void Sys_EnableLog(bool enable)
{
	g_enable_log = enable;
}

void Sys_Log(char *format,...)
{
	if(!g_enable_log) return;
	va_list args;
	va_start(args, format);
	char buf[256];
	VSNPRINTF(buf,255,format,args);
    printf("%s\r\n",buf);
	/* write to file */
	va_end(args);
}

unsigned long Sys_GetTime()
{
#ifdef WIN32
	// return GetTickCount();
	return timeGetTime();
#else 
	/* linux */
	timeval tv;
    gettimeofday(&tv, NULL);
    tv.tv_sec  -= start.tv_sec;
	tv.tv_usec -= start.tv_usec;
	return (tv.tv_sec*1000+tv.tv_usec/1000);
#endif
}

unsigned long Sys_GetSec()
{
	return (unsigned long)time(NULL);	
}

void Sys_Sleep(int ms)
{
#ifdef WIN32
	Sleep(ms);
#else 
	/* linux */
	usleep(ms*1000);
#endif
}

void Sys_CreateConsole(int width, int height)
{
#ifdef WIN32
	HANDLE hStdOut;
    AllocConsole();
    SetConsoleTitleA("Debug Window");
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); 
    COORD co = {width , height};
    SetConsoleScreenBufferSize(hStdOut, co); 
    freopen("CONOUT$","w+t",stdout);
    freopen("CONIN$","r+t",stdin);
#endif
}

unsigned Sys_DoLzwCops(unsigned char *in,unsigned in_len,unsigned char *out,unsigned *out_len)
{
	static long c[16384L] ;
    register unsigned char *i;unsigned char ** j = ( unsigned char ** )c;
	unsigned char *a,*b,*n=in+in_len,*p=in+in_len-13;
    a=out,i=in,b=i;i+=4;
    for (;;) {
		register unsigned char *d;unsigned e,f,g;
		g=((0x21*(((((((unsigned)(i[3])<<6)^i[2])<<5)^i[1])<<5)^i[0]))>>5)&0x3fff;d=j[g];
		if(((unsigned)d<(unsigned)in)||(e=(unsigned)((unsigned)i-(unsigned)d))<=0||e>0xbfff)goto literal;
		if (e<=0x0800||d[3]==i[3])goto try_match;
		g=(g&0x7ff)^0x201f;d=j[g];
		if((unsigned)(d)<(unsigned)(in)||(e=(unsigned)((int)((unsigned)i-(unsigned)d)))<=0||e>0xbfff)goto literal;
		if(e<=0x0800||d[3]==i[3])goto try_match;
		goto literal;
try_match:
		if(*(unsigned short*)d==*(unsigned short*)i&&d[2]==i[2])goto match;
literal:
		j[g]=i++;
		if (i>=p)break;
		continue;
match:
		j[g]=i;
		if(i-b>0){
			register unsigned t=i-b;
			if(t<=3) a[-2]|=(unsigned char)t;
			else if(t<=18)	*a++=(unsigned char)(t-3);
			else{
				register unsigned tt=t-18;*a++=0;
				while(tt>255){tt-=255;*a++=0;}
				*a++=(unsigned char)tt;
			}
			do *a++=*b++; while(--t>0);
		}
		i += 3;
		if (d[3]!=*i++||d[4]!=*i++||d[5]!=*i++||d[6]!=*i++||d[7]!=*i++||d[8]!=*i++){
			--i;f=i-b;
			if(e<=0x0800){--e;*a++=(unsigned char)(((f-1)<<5)|((e&7)<<2));*a++=(unsigned char)(e>>3);}
			else if(e<=0x4000){--e;*a++=(unsigned char)(32|(f-2));goto m3_m4_offset;}
			else {e-=0x4000;*a++=(unsigned char)(16|((e&0x4000)>>11)|(f-2));goto m3_m4_offset;}
		}else{
			{unsigned char *end=n;unsigned char *m=d+9;while(i<end&&*m==*i)m++,i++;f=(i-b);}
			if(e<=0x4000){--e;if(f<=33)*a++=(unsigned char)(32|(f-2));else{f-=33;*a++=32;goto m3_m4_len;}}
			else{
				e-=0x4000;
				if(f<=9)*a++=(unsigned char)(16|((e&0x4000)>>11)|(f-2));
				else{f-=9;*a++=(unsigned char)(16|((e&0x4000)>>11));
m3_m4_len:
				while(f>255){f-=255;*a++=0;}
				*a++ = (unsigned char)f;
				}
			}
m3_m4_offset:
			*a++=(unsigned char)((e&63)<<2);*a++=(unsigned char)(e>>6);
		}
		b=i;
		if(i>=p)break;
    }
    *out_len=a-out;
    return (unsigned) (n - b);
}

int	Sys_LzwComp(void *in,unsigned in_len,void *out)
{
    unsigned char *a=(unsigned char*)out;unsigned t,out_len;
    if(in_len<=13)t = in_len;
    else{t=Sys_DoLzwCops((unsigned char*)in,in_len,a,&out_len);a+=out_len;}
    if(t>0){
		unsigned char *b=(unsigned char*)in+in_len-t;
		if(a==(unsigned char*)out&&t<=238)*a++=(unsigned char)(17+t);
		else if(t<=3)a[-2]|=(unsigned char)t ;
		else if(t<=18)*a++=(unsigned char)(t-3);
		else {unsigned tt=t-18;*a++=0;while(tt>255){tt-=255;*a++=0;}*a++=(unsigned char)tt;}
		do *a++=*b++; while(--t>0);
    }
    *a++=17;*a++=0;*a++=0;
    return(a-(unsigned char*)out);
}

int	Sys_LzwUncomp(void *in,unsigned in_len,void *out)
{
	register unsigned char *a,*i,*d;
	register unsigned t;
	unsigned char *p=(unsigned char*)in+in_len;
	a=(unsigned char*)out;i=(unsigned char*)in;
	if(*i>17){
		t=*i++-17;
		if(t<4)goto match_next;
		do *a++=*i++; while(--t>0);
		goto first_literal_run;
	}
	while(1){
		t=*i++;
		if(t>=16389)
		{
			return 16389;
		}
		if(t>=16)goto match;
		if(t==0){while(*i==0){t+=255;i++;}t+=15+*i++;}
		if(t>=16389)
		{
			return 16389;
		}
		*(unsigned*)a=*(unsigned*)i;a+=4;i+=4;
		if(--t>0){
			if (t >= 4){do{*(unsigned*)a=*(unsigned*)i;a+=4;i+=4;t-=4;}while(t>=4);if(t>0)do*a++=*i++;while(--t>0);}
			else do*a++=*i++;while(--t>0);
		}
first_literal_run:
		t=*i++;
		if(t>=16)goto match;
		d=a-0x0801;d-=t>>2;d-=*i++<<2;*a++=*d++;*a++=*d++;*a++=*d;
		goto match_done;
		while (1){
match:
		if(t>=64){d=a-1;d-=(t>>2)&7;d-=*i++<<3;t=(t>>5)-1;goto copy_match;}
		else if(t>=32){
			t&=31;
			if(t==0){while(*i==0){t+=255;i++;}t+=31+*i++;}
			d=a-1;d-=(*(unsigned short*)i)>>2;i+=2;
		}
		else if(t>=16){
			d=a;d-=(t&8)<<11;t&=7;
			if(t==0){while(*i==0){t+=255;i++;}t+=7+*i++;}
			d-=(*(unsigned short*)i)>>2;i+=2;
			if(d==a)goto eof_found;
			d-=0x4000;
		}else{d=a-1;d-=t>>2;d-=*i++<<2;*a++=*d++;*a++=*d;goto match_done;}
		if (t >= 6 && (a - d) >= 4) {
			* (unsigned *) a = * ( unsigned *) d;
			a += 4; d += 4; t -= 2;
			do {*(unsigned*)a=*(unsigned*)d;a+=4;d+=4;t-=4;}while(t>=4);
			if(t>0)do*a++=*d++;while(--t>0);
		}else{
copy_match:
		*a++=*d++;*a++=*d++;
		do*a++=*d++;while(--t>0);
		}
match_done:
		t=i[-2]&3;
		if(t==0)break;
match_next:
		do*a++=*i++;while(--t>0);
		t=*i++;
		}
	}
eof_found:
	if(i!=p)return-1;
	return(a-(unsigned char*)out);
}

int Sys_EscapeString(const char *from,char escape,char *to,int len)
{
	int total = 0;
	while(*from)
	{
		if(total >= len) return 0;
		if(*from == escape)
		{
			*to++ = '\\';
			*to++ = *from++;
			total += 2;
			continue;
		}
		
		switch(*from)
		{
			case '\\':
				*to++= '\\';
				*to++= *from++;
				total += 2;
				break;
			
			default:
			  *to++= *from++;
			  total++;
		}
	}
	*to = '\0';
	return total;
}

int Sys_GetString(const char *from,char escape,char *to,int len)
{
	int total = 0;
	while(*from)
	{
		if(total >= len) return 0;
		
		if(*from == escape) {
			total++;
			*to = '\0';
			return total;
		}
		
		if(*from == '\\' && from[1])
		{
			total++;
			from++;
		}
		*to++= *from++;
		total++;
	}
	*to = '\0';
	return total;
}



unsigned short iconv_convert(
	void *src,
	unsigned int src_len,
	char *src_charset,
	void *dest,
	unsigned int dest_len,
	char *dest_charset
	)
{
#ifndef GAME_SERVER
	const char* in;
	char *out,*dest_ptr;
	size_t in_left,out_left,mutant,converted;
	in_left=src_len;
	out_left=dest_len;
	in=(char *)src; //特别重要:只有变量才有地址，地址没有地址。可加const
	out=dest_ptr=(char *)dest;
	iconv_t oConv=iconv_open(dest_charset,src_charset);
	if(oConv==(iconv_t)(-1))
	{
		printf("ERROR: unable to open libiconv.");
		return 0;
	}
	mutant=iconv(
		oConv,
		&in,//特别重要:只有变量才有地址，地址没有地址
		&in_left,
		&out,
		&out_left
		);
	iconv_close(oConv);
	if(mutant==(size_t)(-1))
	{
		printf("ERROR: unable to convert anything.");
		return 0;
	}
	converted=dest_len-out_left;
	//printf("to convert %u characters, %u mutanted , %u converted \n",src_len,mutant,converted);
	dest_ptr[converted]='\0';
#endif
	return 1;
}
