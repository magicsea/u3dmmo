using System;
using System.Collections.Generic;

namespace AssemblyCSharp
{	
	public interface Handler
	{
        //public Handler() { }
        void onPacket(WorldPack pack);
        
	}
}
