using System;

namespace AssemblyCSharp
{
	// size will only apply on created.so write data carefully or apply enough mem for it.
	public class WorldPack : ByteBuffer
	{

        public bool isSystem = false;
        public bool isCompress = false;
        public bool isEncode = false;

        private Opcodes _opcode;
        public Opcodes opcode() { return _opcode; }

        public WorldPack()
            : base()
        {
        }
        public WorldPack(Opcodes opcode)
            : base()
		{
			_opcode = opcode;			
		}
        public WorldPack(UInt16 size, bool sys, bool comp, bool encode)
            :base(size)
        {
            isSystem = sys;
            isCompress = comp;
            isEncode = encode;
        }

        public WorldPack(Opcodes opcode, UInt16 size)
            : base(size)
		{
			_opcode = opcode;
		}	

	}
}

