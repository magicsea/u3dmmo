#include "md5.h"

// ---------------------------------------------------------------------------------------------------------------------

GMD5::GMD5() 
{
	memset(m_buffer, 0, 64);
	
	m_nCount[0] = 0;
	m_nCount[1] = 0;

	m_anMD5[0] = MD5_INIT_STATE_0;
	m_anMD5[1] = MD5_INIT_STATE_1;
	m_anMD5[2] = MD5_INIT_STATE_2;
	m_anMD5[3] = MD5_INIT_STATE_3;
	
	memset(m_padding, 0, 64);
	m_padding[0] = 0x80;
}

// ---------------------------------------------------------------------------------------------------------------------

GMD5::~GMD5() 
{

}
		
// ---------------------------------------------------------------------------------------------------------------------

void GMD5::GetMD5(const char* pInput, DWORD nInputLen, BYTE *pOutput)
{
	GMD5 		temp;
	
	temp.Update((BYTE *)pInput, nInputLen);
	temp.Final();

	strcpy((char *)pOutput, temp.m_result);
}

// ---------------------------------------------------------------------------------------------------------------------

void GMD5::Update(BYTE* pInput, DWORD nInputLen)
{
	DWORD					nIndex;
	DWORD					i;
	DWORD					nPartLen;
	
	nIndex = (DWORD)((m_nCount[0] >> 3) & 0x3F);
	if((m_nCount[0] += nInputLen << 3) < (nInputLen << 3))
		m_nCount[1]++;
	
	m_nCount[1] += (nInputLen >> 29);

	i=0;		
	nPartLen = 64 - nIndex;
	if(nInputLen >= nPartLen) 	
	{
		memcpy(&m_buffer[nIndex], pInput, nPartLen);
		Transform(m_buffer);
		for(i = nPartLen; i+63 < nInputLen; i += 64) 
			Transform(&pInput[i]);
		
		nIndex = 0;
	} 
	else 
	{
		i = 0;
	}

	memcpy(&m_buffer[nIndex], &pInput[i], nInputLen-i);
}

// ---------------------------------------------------------------------------------------------------------------------

void GMD5::Final()
{
	BYTE 			bits[8];
	DWORD			nIndex;
	DWORD			nPadLen;
	BYTE 			acMD5[16];
		
	DWordToByte(m_nCount, bits, 8);

	nIndex = (DWORD)((m_nCount[0] >> 3) & 0x3f);
	nPadLen = (nIndex < 56) ? (56 - nIndex) : (120 - nIndex);
	
	Update(m_padding, nPadLen);
	Update(bits, 8);

	DWordToByte(m_anMD5, acMD5, 16);
	m_result[0] = '\0';
	for(int i=0; i < 16; i++) 
	{
		char		acTemp[8];
		
		if(acMD5[i] == 0) 
		{
			strcpy(acTemp, "00");
		}
		else
		{ 
			if(acMD5[i] <= 15) 	
			{
				sprintf(acTemp, "0%x", acMD5[i]);
			}
			else 
			{
				sprintf(acTemp, "%x", acMD5[i]);
			}
		}
		
		strcat(m_result, acTemp);
	}
}

// ---------------------------------------------------------------------------------------------------------------------

void GMD5::Transform(BYTE block[64])
{
	DWORD			a, b, c, d;
	DWORD 			X[16];
	
	a = m_anMD5[0];
	b = m_anMD5[1];
	c = m_anMD5[2];
	d = m_anMD5[3];

	ByteToDWord(block, X, 64);

	FF (a, b, c, d, X[ 0], MD5_S11, MD5_T01); 
	FF (d, a, b, c, X[ 1], MD5_S12, MD5_T02); 
	FF (c, d, a, b, X[ 2], MD5_S13, MD5_T03); 
	FF (b, c, d, a, X[ 3], MD5_S14, MD5_T04); 
	FF (a, b, c, d, X[ 4], MD5_S11, MD5_T05); 
	FF (d, a, b, c, X[ 5], MD5_S12, MD5_T06); 
	FF (c, d, a, b, X[ 6], MD5_S13, MD5_T07); 
	FF (b, c, d, a, X[ 7], MD5_S14, MD5_T08); 
	FF (a, b, c, d, X[ 8], MD5_S11, MD5_T09); 
	FF (d, a, b, c, X[ 9], MD5_S12, MD5_T10); 
	FF (c, d, a, b, X[10], MD5_S13, MD5_T11); 
	FF (b, c, d, a, X[11], MD5_S14, MD5_T12); 
	FF (a, b, c, d, X[12], MD5_S11, MD5_T13); 
	FF (d, a, b, c, X[13], MD5_S12, MD5_T14); 
	FF (c, d, a, b, X[14], MD5_S13, MD5_T15); 
	FF (b, c, d, a, X[15], MD5_S14, MD5_T16); 

	GG (a, b, c, d, X[ 1], MD5_S21, MD5_T17); 
	GG (d, a, b, c, X[ 6], MD5_S22, MD5_T18); 
	GG (c, d, a, b, X[11], MD5_S23, MD5_T19); 
	GG (b, c, d, a, X[ 0], MD5_S24, MD5_T20); 
	GG (a, b, c, d, X[ 5], MD5_S21, MD5_T21); 
	GG (d, a, b, c, X[10], MD5_S22, MD5_T22); 
	GG (c, d, a, b, X[15], MD5_S23, MD5_T23); 
	GG (b, c, d, a, X[ 4], MD5_S24, MD5_T24); 
	GG (a, b, c, d, X[ 9], MD5_S21, MD5_T25); 
	GG (d, a, b, c, X[14], MD5_S22, MD5_T26); 
	GG (c, d, a, b, X[ 3], MD5_S23, MD5_T27); 
	GG (b, c, d, a, X[ 8], MD5_S24, MD5_T28); 
	GG (a, b, c, d, X[13], MD5_S21, MD5_T29); 
	GG (d, a, b, c, X[ 2], MD5_S22, MD5_T30); 
	GG (c, d, a, b, X[ 7], MD5_S23, MD5_T31); 
	GG (b, c, d, a, X[12], MD5_S24, MD5_T32); 

	HH (a, b, c, d, X[ 5], MD5_S31, MD5_T33); 
	HH (d, a, b, c, X[ 8], MD5_S32, MD5_T34); 
	HH (c, d, a, b, X[11], MD5_S33, MD5_T35); 
	HH (b, c, d, a, X[14], MD5_S34, MD5_T36); 
	HH (a, b, c, d, X[ 1], MD5_S31, MD5_T37); 
	HH (d, a, b, c, X[ 4], MD5_S32, MD5_T38); 
	HH (c, d, a, b, X[ 7], MD5_S33, MD5_T39); 
	HH (b, c, d, a, X[10], MD5_S34, MD5_T40); 
	HH (a, b, c, d, X[13], MD5_S31, MD5_T41); 
	HH (d, a, b, c, X[ 0], MD5_S32, MD5_T42); 
	HH (c, d, a, b, X[ 3], MD5_S33, MD5_T43); 
	HH (b, c, d, a, X[ 6], MD5_S34, MD5_T44); 
	HH (a, b, c, d, X[ 9], MD5_S31, MD5_T45); 
	HH (d, a, b, c, X[12], MD5_S32, MD5_T46); 
	HH (c, d, a, b, X[15], MD5_S33, MD5_T47); 
	HH (b, c, d, a, X[ 2], MD5_S34, MD5_T48); 

	II (a, b, c, d, X[ 0], MD5_S41, MD5_T49); 
	II (d, a, b, c, X[ 7], MD5_S42, MD5_T50); 
	II (c, d, a, b, X[14], MD5_S43, MD5_T51); 
	II (b, c, d, a, X[ 5], MD5_S44, MD5_T52); 
	II (a, b, c, d, X[12], MD5_S41, MD5_T53); 
	II (d, a, b, c, X[ 3], MD5_S42, MD5_T54); 
	II (c, d, a, b, X[10], MD5_S43, MD5_T55); 
	II (b, c, d, a, X[ 1], MD5_S44, MD5_T56); 
	II (a, b, c, d, X[ 8], MD5_S41, MD5_T57); 
	II (d, a, b, c, X[15], MD5_S42, MD5_T58); 
	II (c, d, a, b, X[ 6], MD5_S43, MD5_T59); 
	II (b, c, d, a, X[13], MD5_S44, MD5_T60); 
	II (a, b, c, d, X[ 4], MD5_S41, MD5_T61); 
	II (d, a, b, c, X[11], MD5_S42, MD5_T62); 
	II (c, d, a, b, X[ 2], MD5_S43, MD5_T63); 
	II (b, c, d, a, X[ 9], MD5_S44, MD5_T64); 

	m_anMD5[0] += a;
	m_anMD5[1] += b;
	m_anMD5[2] += c;
	m_anMD5[3] += d;
}

// ---------------------------------------------------------------------------------------------------------------------

void GMD5::ByteToDWord(BYTE* pByte, DWORD* pDword, DWORD nByteLen)
{
	DWORD 			i=0;	
	DWORD 			j=0;	

	for ( ; j<nByteLen; i++, j += 4)
	{
		pDword[i] = (DWORD)pByte[j] | ((DWORD)pByte[j+1])<<8 | 
					 ((DWORD)pByte[j+2])<<16 | ((DWORD)pByte[j+3]) << 24;
	}	
}

// ---------------------------------------------------------------------------------------------------------------------

void GMD5::DWordToByte(DWORD* pDword, BYTE* pByte, DWORD nByteLen)
{
	DWORD 			i = 0;
	DWORD 			j = 0;
	
	for( ; j<nByteLen; i++, j += 4) 
	{
		pByte[j] =   (BYTE)(pDword[i] & 0xff);
		pByte[j+1] = (BYTE)((pDword[i] >> 8) & 0xff);
		pByte[j+2] = (BYTE)((pDword[i] >> 16) & 0xff);
		pByte[j+3] = (BYTE)((pDword[i] >> 24) & 0xff);
	}
}

// ---------------------------------------------------------------------------------------------------------------------

void GMD5::FF(DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T)
{
	DWORD 		F;
	
	F = (B & C) | (~B & D);
	A += F + X + T;
	A = RotateLeft(A, S);
	A += B;
}

// ---------------------------------------------------------------------------------------------------------------------

void GMD5::GG(DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T)
{
	DWORD 		G;
	
	G = (B & D) | (C & ~D);
	A += G + X + T;
	A = RotateLeft(A, S);
	A += B;
}

// ---------------------------------------------------------------------------------------------------------------------

void GMD5::HH(DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T)
{
	DWORD		H; 
	
	H = (B ^ C ^ D);
	A += H + X + T;
	A = RotateLeft(A, S);
	A += B;
}

// ---------------------------------------------------------------------------------------------------------------------

void GMD5::II(DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T)
{
	DWORD 		I;
	
	I = (C ^ (B | ~D));
	A += I + X + T;
	A = RotateLeft(A, S);
	A += B;
}

// ---------------------------------------------------------------------------------------------------------------------

DWORD GMD5::RotateLeft(DWORD x, int n)
{
	return (x << n) | (x >> (32-n));
}
