using System;
using System.Collections;
using System.Collections.Generic;

//#define printf Console.Write

namespace AssemblyCSharp
{
		
	// use for hold data.
	public class ByteBuffer
	{
		public static UInt16  DEFAULT_SIZE = 0x1000;

		public ByteBuffer()
		{
            _storage = new byte[DEFAULT_SIZE];
			_asize = DEFAULT_SIZE;
            _wpos = _rpos = 0;
            _size = 0;
		}

        public ByteBuffer(UInt16 size)
		{
			_storage = new byte[size];
			_asize = size;
            _wpos = _rpos = 0;
            _size = 0;
		}
		
		// not test yet.
		public ByteBuffer(byte[]data, int startIndex)
		{
			int cnt = data.Length - startIndex;
			System.Diagnostics.Debug.Assert(cnt>0);
			
			_storage = new byte[cnt];
			_asize = (UInt16)cnt;
            _wpos = _rpos = 0;
            _size = 0;
			
			Array.Copy(data,startIndex,_storage,_wpos,cnt);			
			_wpos += (UInt16)cnt;
			_size += (UInt16)cnt;
		}
		
		
		
		protected int _wpos,_rpos;
        protected UInt16 _size, _asize; // _size is the truely size, _asize is the allocated mem for this pack. we did not handle the sisuation if  _size > _asize. so let the init size big enough.
		protected byte[] _storage = null;  // pakce data storage.		protected List<byte> _storage = new List<byte>(); I hope it could be dynamic.
		
		//public int size(){ return _size;}
		public byte[] contents(){ return _storage;}
		public UInt16 size() { return _size; }
        public void wpos(UInt16 pos) { _wpos = pos; }

		public void check(){ System.Diagnostics.Debug.Assert(_size == _storage.Length); }

        public void append(byte[] src, int startIndex, int lenth)
        {
            int cnt = src.GetLength(0);
            if (cnt <= 0) return;
            System.Diagnostics.Debug.Assert(cnt >= startIndex + lenth);
            Array.Copy(src, startIndex, _storage, _wpos, lenth);
            _wpos += lenth;
            _size += (UInt16)lenth;	
        }

        public void append(byte[] src, int size)
        {
            int cnt = (src.GetLength(0));
            cnt = cnt < size ? cnt : size;
            if (cnt <= 0) return;
            System.Diagnostics.Debug.Assert(_asize >= _size + cnt); // packetes should large than expected.

            Array.Copy(src, 0, _storage, _wpos, cnt);
            _wpos += cnt;
            _size += (UInt16)cnt;
        }

		public void append( byte[] src )
		{			
			int cnt = (src.GetLength(0));
			if(cnt<=0) return;			
			System.Diagnostics.Debug.Assert (_asize>=_size+cnt); // packetes should large than expected.

			Array.Copy(src,0,_storage,_wpos,cnt);			
			_wpos += cnt;
            _size += (UInt16)cnt;			
		}	
		
		public void W(ByteBuffer cp)
		{
			append (cp.contents(),cp.size());
		}
		
		public void W(char value)
		{		
			byte[] src = BitConverter.GetBytes(value);		
			append(src);
		}
		
		public void W(bool value)
		{		
			byte[] src = BitConverter.GetBytes(value);		
			append(src);
		}
		public void W(int value)
		{
			byte[] src = BitConverter.GetBytes(value);		
			append(src);
		}
        public void W(short value)
        {
            byte[] src = BitConverter.GetBytes(value);
            append(src);
        }
        public void W(byte value)
        {
            byte[] src = new byte[1];
            src[0] = value;
            append(src);
        }
        public void W(float value)
        {
            byte[] src = BitConverter.GetBytes(value);
            append(src);
        }
		public void W(UInt16 value)
		{
			byte[] src = BitConverter.GetBytes(value);		
			append(src);
		}
		public void W(UInt32 value)
		{
			byte[] src = BitConverter.GetBytes(value);		
			append(src);
		}
        public void w(Int64 value)
        {
            byte[] src = BitConverter.GetBytes(value);
            append(src);
        }
		public void W(String value)
		{            
            byte[] src = System.Text.Encoding.UTF8.GetBytes (value);
            byte[] srcNew = new byte[src.Length + 1];//最后添加"\0" 为了配合老的服务器格式
            Array.Copy(src, 0, srcNew, 0, src.Length);
            srcNew[src.Length] = (byte)'\0';
            W((UInt16)srcNew.Length);
            append(srcNew);		
            //W((byte)0); // do not input char, it take 2byte
		}
		
		// unsigned 这个方法有bug, to char 返回是unicode char 占用2个字节。暂时取消这个方法。
        //public void R(ref char value)
        //{			
        //    value = BitConverter.ToChar(_storage,_rpos);		
        //    _rpos += 1; // char 1 byte on c#.
        //}

        public void R(ref byte value)
        {
            value = _storage[_rpos];
            _rpos += 1; // boolean 1 byte on c#.
        }
		public void R(ref bool value)
		{
			
			value = BitConverter.ToBoolean(_storage,_rpos);		
			_rpos += 1; // boolean 1 byte on c#.
		}
        //public void R(ref Int16 value)
        //{
        //    value = BitConverter.ToInt16(_storage, _rpos);
        //    _rpos += 2; // int16 == int 16 1 bytes;
        //}
        public void R(ref Int32 value)
        {
            value = BitConverter.ToInt32(_storage, _rpos);
            _rpos += 4; // int == int 32 5 bytes;
        }
        public void R(ref short value)
        {
            value = BitConverter.ToInt16(_storage, _rpos);
            _rpos += 2; // int == int 32 5 bytes;
        }

        public void R(ref float value)
        {
            value = BitConverter.ToSingle(_storage, _rpos);
            _rpos += 4; // float 4 bytes.
        }
		
		public void R(ref UInt16 value)
		{			
			value = BitConverter.ToUInt16(_storage,_rpos);		
			_rpos += 2; // uint16 2 bytes.
		}
		public void R(ref UInt32 value)
		{			
			value = BitConverter.ToUInt32(_storage,_rpos);		
			_rpos += 4; // uint16 2 bytes.
		}
        public void R(ref Int64 value)
        {
            value = BitConverter.ToInt64(_storage, _rpos);
            _rpos += 8; // int == int 64 8 bytes;
        }
		public void R(ref string value)
		{
            // server string will end with 0.
            //value = "";
            //while (true)
            //{
            //    char c = (char)0;
            //    R(ref c);
            //    if (c == 0)
            //        break;
            //    value += c;
            //}
            value = "";
            
            UInt16 size = 0;
            R(ref size);
            if (size > 0)
            {
                //value = BitConverter.ToString(_storage, _rpos, size);

                byte[] str = new byte[size];                
                Array.Copy(_storage, _rpos, str, 0, size);
                _rpos += size;
                try
                {
                    //最后添加"\0" 为了配合老的服务器格式
                    str[str.Length - 1] = (byte)'\0';

                    value = System.Text.Encoding.UTF8.GetString(str);

                }
                catch (Exception e)
                {
                    Console.WriteLine(e.ToString());
                }
            }			
		}	
		
		// const uint8[] contents() const { return _storage.[0]; };

		


	}
}

