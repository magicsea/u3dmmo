using UnityEngine;
using System;
using System.Collections.Generic;
namespace AssemblyCSharp
{

    public sealed class rpc
    {
        #region "acess stuff"
        static readonly rpc instance=new rpc();

        // Explicit static constructor to tell C# compiler
        // not to mark type as beforefieldinit
        static rpc()
        {
        }

        private rpc()
        {

        }

        public static rpc Instance
        {
            get
            {
                return instance;
            }
        }
        #endregion

        #region "rpc stuff""
        const UInt32 LUA_TBOOLEAN = 1;  // BOOL
        const UInt32 LUA_TLIGHTUSERDATA = 2; // no use
        const UInt32 LUA_TBNUMBER = 3;  // INT32
        const UInt32 LUA_TSTRING = 4;   // string
        const UInt32 LUA_TTABLE = 5;    // no use
        const UInt32 LUA_TFUNCTION = 6; // no use
        const UInt32 LUA_TUSERDATA = 7; // INT64
        const UInt32 LUA_TTHREAD = 8; // no use
        
        private Dictionary<string, Delegate> rpcs = new Dictionary<string, Delegate>();
        private List<WorldPack> packs = new List<WorldPack>();
        private bool enable = true;
        public delegate void CM0();
        public delegate void CM1<a>(a _a);
        public delegate void CM2<a, b>(a _a, b _b);
        public delegate void CM3<a, b, c>(a _a, b _b, c _c);
        public delegate void CM4<a, b, c, d>(a _a, b _b, c _c, d _d);
        public delegate void CM5<a, b, c, d, e>(a _a, b _b, c _c, d _d, e _e);
        public delegate void CM6<a, b, c, d, e, f>(a _a, b _b, c _c, d _d, e _e, f _f);
        public delegate void CM7<a, b, c, d, e, f, g>(a _a, b _b, c _c, d _d, e _e, f _f, g _g);
        public delegate void CM8<a, b, c, d, e, f, g, h>(a _a, b _b, c _c, d _d, e _e, f _f, g _g, h _h);
        public delegate void CM9<a, b, c, d, e, f, g, h, l>(a _a, b _b, c _c, d _d, e _e, f _f, g _g, h _h,l _l);
        #endregion
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        #region "rpc method""

        public static void init()
        {   
            rpc.Instance.regist("a", new rpc.CM0(a));
            clearRpcIDs();
        }

        static float[] s_times = new float[10];
        static int s_index1 = 0;
        static int s_index2 = 0;

        public static void clearRpcIDs()
        {
            s_index1 = 0;
            s_index2 = 0;
        }

        static bool isRpcFull()
        {
            return s_index1 == ((s_index2 + 1) % s_times.Length);
        }

        static bool isRpcEmpty()
        {
            return s_index1 == s_index2;
        }

        static int getRpcCount()
        {
            return (s_index2 - s_index1 + s_times.Length) % s_times.Length;
        }

        public bool reconnectTry=false;
		public bool reconnecting=false;
        public void callServerMethod(string methodName, params object[] par)
        {
            if (Net.s_loginSocket != null)
            {
                WorldPack pack = rpcToPack(methodName, par);
                if (Net.s_loginSocket.connected())
                {
                    Log("C-> " + methodName);                    
                    Net.s_loginSocket.OutPacket(pack);
					
                    WorldPack apack = rpcToPack("a");
                    Net.s_loginSocket.OutPacket(apack);
                    if (!isRpcFull())
                    {
                        s_times[s_index2] = Time.realtimeSinceStartup;
                        s_index2 = (s_index2 + 1) % s_times.Length;
                    }
                    else
                    {
                        Debug.LogWarning("RPC: ack full");                        
                    }
                }
                else if (true == reconnectTry && false == reconnecting)
                {
                    Log("reconnecting .......................");                   
                    lastPack = pack;
                    //ModalMsg.showMessage("正在重新连接... ...");
                    Net.s_loginSocket.Disconnect();
                    Net.s_loginSocket.ReConnect();
					reconnecting=true;
                }
            }
        }

        static void a()
        {
            if (!isRpcEmpty())
            {
                float t = Time.realtimeSinceStartup - s_times[s_index1];
				s_index1 = (s_index1 + 1) % s_times.Length;     
                
				if (t>0.02)
				{
                	Debug.LogWarning("RPC: back time: " +  t);            
					Log(" left rpc count: " + getRpcCount()); 
				}                
            }
            else
            {
                Debug.LogWarning("RPC: ack empty");
            }
        }

        public static float getDelayTime()
        {
            if (!isRpcEmpty())
            {
                return (Time.realtimeSinceStartup - s_times[s_index1]);
            }
            
            return 0;
        }

        WorldPack rpcToPack(string methodName, params object[] par)
        {
            WorldPack pack = new WorldPack(Opcodes.CMSG_GODMODE, (UInt16)(methodName.Length * 2 + 2 + 8000));
            UInt32 prams = 0;
            pack.W(prams);
            pack.W(methodName);
            int count = 0;
            UInt32 type = 0;
            foreach (object ob in par)
            {
                if (ob is System.Int32)
                {
                    pack.W((Int32)ob);
                    type = LUA_TBNUMBER;
                }
                else if (ob is System.Int16)
                {
                    Int16 temp = (Int16)ob;
                    pack.W((Int32)temp);
                    type = LUA_TBNUMBER;
                }
                else if (ob is System.UInt16)
                {
                    UInt16 temp = (UInt16)ob;
                    pack.W((Int32)temp);
                    type = LUA_TBNUMBER;
                }
                else if (ob is System.UInt32)
                {
                    pack.W((UInt32)ob);
                    type = LUA_TFUNCTION;
                }
                else if (ob is System.Int64)
                {
                    Int64 temp = (Int64)ob;
                    pack.W((Int64)temp);
                    type = LUA_TUSERDATA;
                }
                else if (ob is System.Boolean)
                {                    
                    pack.W((Boolean)ob);
                    type = LUA_TBOOLEAN;
                }
                else if (ob is System.String)
                {
                    pack.W((string)ob);
                    type = LUA_TSTRING;
                }
                else
                {                    
                    Debug.LogError("RPC: callServerMethod Got unknown data type methods");
                }

                prams = (prams | (type & 0xf) << 3 * count++);
            }
            pack.wpos(0);
            pack.W(prams);

            return pack;
        }
  
        public void resend()
        {
            if (lastPack != null)
            {
                Net.s_loginSocket.OutPacket(lastPack);
                lastPack = null;
            }
        }

        private WorldPack lastPack = null;
        private void _handleTable(WorldPack pack)
        {
            return;
        }

        public void enabled()
        {            
            enable = true;
            for (int i = 0; i < packs.Count; i++)
            {
                _handleRPC((WorldPack)packs[i]);
            }
           
            Log("enabled client rpc process. process buffer" + packs.Count + " worldpackets");
            packs.Clear();
        }

        public void disable()
        {            
            Log(" disable client rpc process");
            enable = false;
        }

        private void _handleRPC(WorldPack pack)
        {
            //receive            
            if (false == enable)
            {               
				Debug.LogWarning("RPC: we stoped rpc ,waiting for resume" );
                packs.Add(pack);
                return;
            }

            UInt32 prams = 0;
            pack.R(ref prams);
            string methodName = "";
            pack.R(ref methodName);

            string des = methodName;
            des += "(";
            List<object> pramList = new List<object>();
            int count = 0;
            UInt32 type = (prams >> (3 * count) & 7);

            while (type != 0)
            {
                switch (type)
                {
                    case LUA_TBOOLEAN:
                        {
                            Boolean value = false;
                            pack.R(ref value);
                            pramList.Add(value);
                            des += value.ToString();
                            des += " , ";
                        }
                        break;
                    case LUA_TUSERDATA:
                        {
                            Int64 value = 0;
                            pack.R(ref value);
                            pramList.Add(value);
                            des += "[Int64]";
                            des += value.ToString();
                            des += " , ";                            
                        }
                        break;
                    //case LUA_TTHREAD:
                    //    {
                    //        UInt64 value = 0;
                    //        pack.R(ref value);
                    //        pramList.Add(value);
                    //        des += value.ToString();
                    //        des += " , ";
                    //    }
                    //    break;
                    case LUA_TBNUMBER:
                        {
                            Int32 value = 0;
                            pack.R(ref value);
                            pramList.Add(value);
                            des += "[Int32]";
                            des += value.ToString();
                            des += " , ";
                        }
                        break;
                    case LUA_TSTRING:
                        {
                            string value = "";
                            pack.R(ref value);
                            pramList.Add(value);
                            des += "[String]";
                            des += value.ToString();
                            des += " , ";
                        }
                        break;
                    default:
						{
                            Debug.LogWarning("RPC: callClientMethod Got unknown data type methods");
                        }
                        break;
                }
                count++;
                type = (prams >> (3 * count) & 7);
            }
            des += " ) ";
			if (methodName != "a")
			{
            	Log("S->  " + des );        
			}
            _callClientMethod(methodName, pramList);
        }

        private void _callClientMethod(string name, List<object> list)
        {
            if (!rpcs.ContainsKey(name))
            {               
                Debug.LogWarning("RPC:callClientMethod-> can not find client function[" + name + "].");
                return;
            }
            Delegate f = rpcs[name];
            int no = list.Count;
            int pra = 0;

            //try
            {
                switch (no)
                {
                    case 0:
                        f.DynamicInvoke();
                        break;
                    case 1:
                        f.DynamicInvoke(list[pra++]);
                        break;
                    case 2:
                        f.DynamicInvoke(list[pra++], list[pra++]);
                        break;
                    case 3:
                        f.DynamicInvoke(list[pra++], list[pra++], list[pra++]);
                        break;
                    case 4:
                        f.DynamicInvoke(list[pra++], list[pra++], list[pra++], list[pra++]);
                        break;
                    case 5:
                        f.DynamicInvoke(list[pra++], list[pra++], list[pra++], list[pra++], list[pra++]);
                        break;
                    case 6:
                        f.DynamicInvoke(list[pra++], list[pra++], list[pra++], list[pra++], list[pra++], list[pra++]);
                        break;
                    case 7:
                        f.DynamicInvoke(list[pra++], list[pra++], list[pra++], list[pra++], list[pra++], list[pra++], list[pra++]);
                        break;
                    case 8:
                        f.DynamicInvoke(list[pra++], list[pra++], list[pra++], list[pra++], list[pra++], list[pra++], list[pra++], list[pra++]);
                        break;
                    default:
                        break;
                }
            }
            //catch (Exception e)
           // {
            //    Debug.LogError("RPC: Exception: " + e.Message);                
           // }
        }
        #endregion
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        public void regist(string name, Delegate func)
        {
            if (rpcs.ContainsKey(name)) 
            { 
                Debug.LogWarning("RPC: 重复注册的rpc方法 [" + name+ "]");               
            }
            rpcs[name] = func;
        }
		
		static public void Log(string info)
		{
			Debug.Log ("RPC: "+info);
		}
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        public LoginSocket h;                                          // using for sending packet
        public void onPakcet(WorldPack packet) { _handleRPC(packet); } // handle packet
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }

};
