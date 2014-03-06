using UnityEngine;
using System;
using System.Net.Sockets;
using System.Net;
using System.Collections.Generic;
using System.Threading;

namespace AssemblyCSharp
{	
	// gamelogic->worldpack(encrpt compress)->socketsend and receive
	// conncet timeout disconncect
	public class Socket
	{		
		private TcpClient _tcpClient = null;
		private string _address="127.0.0.1";
		private int _port=8093;		// login port, game port.
        private int _timeoutMSec = 1000;
		// two buffer for read and write data for socket
		private byte[] _read = new byte[10240]; // use to hold data form FD.
		//private byte[] _write = new byte[512]; // once write world pack is build, data will send to socket imediately. so do we need a buffer?
		private NetworkStream _netStream = null;
		private UInt16 _rpos,_wpos = 0;

		// private PacketHandler PH = null; will handel those msg due to the pack id given.

		public Socket()
		{             
		}
		
		public Socket (string address,int port)
		{
			_address = address;
			_port = port;         
		}

        public bool connected() { return (null != _tcpClient ? _tcpClient.Connected : false); }

		public void Destory()
		{
            if (_tcpClient != null)
            {
                _tcpClient.Close(); // may it be gc?
                _tcpClient = null;
            }
			
			if (null != _netStream)
			{
				_netStream.Close();
				_netStream = null;
			}
            _rpos = 0;
            _wpos = 0;
		}
        public bool connecting = false;
        public void ReConnect()
        {
            if (connected()) return;
            Destory();            
            TryToConnect(_address, _port,3000);
        }

        public void TryToConnect(string ip, int port, int timeoutMSec)
        {
            rpc.init();
            //
            _address = ip;
            _port = port;
            _timeoutMSec = timeoutMSec;
//            TryToConnect();
            Thread thread = new Thread(new ThreadStart(TryToConnect));
            thread.IsBackground = true;
            thread.Start();
        }        
                
        private static ManualResetEvent TimeoutObject = new ManualResetEvent(false);
		//event 1 conncet and disconnect.
        public void TryToConnect()
		{
            if (null == _tcpClient) // onDisconnected
				_tcpClient = new TcpClient();

            _tcpClient.NoDelay = true;
			try 
			{
                int okey = _tcpClient.Client.Available;				
			}
			catch(ObjectDisposedException)
			{
                _tcpClient = null;
				_tcpClient=new TcpClient();
			}
			
			if (_tcpClient.Client.Connected == true)
			{
                Debug.Log("Client already connected to the server");
				return;
			}

            connecting = true;
            TimeoutObject.Reset();
            Debug.Log("begin connect: "+_address+":"+_port);
            _tcpClient.BeginConnect(_address, _port, new AsyncCallback(_onConnected), null);
            if (TimeoutObject.WaitOne(_timeoutMSec, false))
            {
                Debug.Log("TimeoutObject.WaitOne " + _timeoutMSec.ToString());
                if (connected())
                {
                    Debug.Log("Connected");
                }
                else
                {
                    Debug.Log("Connect failed!");
                }
            }
            else
            {
                if (!connected())
                {
                    Debug.Log("Connect time out!");
                    _onConnected(null);
                }
            }
            connecting = false;
        }

        //event 1 conncet and disconnect.
        public void Connect(string ip, int port)
        {
            _address = ip;
            _port = port;
//            if (null == _tcpClient) // onDisconnected
                _tcpClient = new TcpClient();

            //_tcpClient.NoDelay = true;
            try
            {
                int okey = _tcpClient.Client.Available;
            }
            catch (ObjectDisposedException)
            {
                _tcpClient = null;
                _tcpClient = new TcpClient();
            }

            if (_tcpClient.Client.Connected == true)
            {
                Console.WriteLine("Client already connected to the server");
                return;
            }

            try
            {
                _tcpClient.Connect(_address, _port);
            }
            catch (System.Net.Sockets.SocketException)
            {
                Console.WriteLine("Client can not connected to the server");
                return;
            }

            _onConnected(null);
        }
		
		
		// once connected. we start to read data and ping.
		private void _onConnected(IAsyncResult result)
		{
            Debug.Log("_onConnected " + _tcpClient.Connected.ToString()+ "  "+result.ToString());
            if (true == _tcpClient.Connected)
            {
                Console.WriteLine("{0} connect to server is successful.",_tcpClient.Client.ToString());
            }
            else
            {
                Console.WriteLine("Connecting error and failed.");
                WorldPack Packet = new WorldPack(Opcodes.SMSG_CONNECT_FAILED, 0);
                if (null != _packHandler)
                {
                    // push into a packet array.
                    addEvent(Packet);
                }
                _tcpClient.Close();
                _tcpClient = null;
                return;
            }
			
			// init stuff.
			_rpos = _wpos = 0;

            Debug.Log("_onConnected read first ");

			_netStream = new NetworkStream(_tcpClient.Client);
			_netStream.BeginRead(
				_read,
				(int)_wpos,
				(int)(_read.Length-_wpos),
				new AsyncCallback(_onRead),
				null);
			// 将下次收发的数据放到 _read _wpos的位置。并调用 onRead处理buffer。
            // init sending pings.
            // SendPing();

            Debug.Log("_onConnected end ");
		}

			// use pingpong to count time out out size.
		public void Disconnect()
		{
			Destory ();
            // tell clients stop to read.
		}
		
		// event 2 ,always successful, if failed, error and log it.
        public const UInt16 MESSAGEHEAD_CODE_LENGTH = sizeof(Opcodes);
        public const UInt16 MESSAGEHEAD_SIZE_LENGTH = sizeof(UInt16);
        public const UInt16 C2S_PACK_HEAD_SIZE = MESSAGEHEAD_CODE_LENGTH + MESSAGEHEAD_SIZE_LENGTH;
        public const UInt16 S2C_PACK_HEAD_SIZE = MESSAGEHEAD_CODE_LENGTH + MESSAGEHEAD_SIZE_LENGTH;

		public void	OutPacket(WorldPack pack)
		{
            if (!connected()) return;
            UInt16 size = (UInt16)(pack.size() + C2S_PACK_HEAD_SIZE);
			ByteBuffer data = new ByteBuffer( size );
            data.W ((UInt16)(pack.size()+4));
            data.W ((UInt32)pack.opcode());			
			data.W (pack);            
			_tcpClient.Client.Send(data.contents());
		}
			
        private List<WorldPack> _events = new List<WorldPack>();
        private List<Opcodes> _missedEvents = new List<Opcodes>();

        private void addEvent(WorldPack Packet)
        {
            lock (_events)
            {
                bool missEvent = false;
                for (int i = 0; i < _missedEvents.Count; i++)
                {
                    if (_missedEvents[i] == Packet.opcode())
                    {
                        _missedEvents.RemoveAt(i);
                        Debug.LogWarning("ignore missed event: " + Packet.opcode() + ", missed events count: " + _missedEvents.Count);
                        missEvent = true;
                        break;
                    }
                }
                if (!missEvent)
                {
                    _events.Add(Packet);
                }
            }
        }
		
		//event 3, do receive stuff for clients.
		// use tcpClients snync reading methods, read them into circular buffer, and make worldpack.		
        // Callback function when receive byte data,Using tcpClient start read sync fucntion.              
        private void _onRead(IAsyncResult result)
        {
            Debug.Log("_onRead " + result.ToString());
            // check if we have been gc or closed.
            if (!connected() || null == _netStream)
            {
                return;
            }

            int readByteThisTime = _netStream.EndRead(result);
            if (readByteThisTime <= 0)
            {
                Debug.LogError("NetErrorCode.NET_RECV_ERROR");
                Console.WriteLine("NetErrorCode.NET_RECV_ERROR");
                Disconnect();
                // TryToConnect();
                return;
            }
            Debug.Log("_onRead Receive beytes " + readByteThisTime.ToString());
            //Console.WriteLine("Receive beytes {0}",readByteThisTime);

            _wpos += (UInt16)readByteThisTime;
            // _wpos 为当前系统向_read中数据写到的长度。指向_read中数据的结尾处。
            // _rpos指向当前读数据开始的位置，只有在成功读出一个包的时候才改变它。                
            // 缓存中当前处理实际数据大小为 _wpos-_rpos.
            // 循环处理多个包之后，缓存中的数据不足以一个包的时候，做自拷贝动作。
            // :将 _rpos --> _wpos的数据拷贝到_read开头。
            // _wpos and _rpos  all --rpos;

            while(true)
            {
                Debug.Log("_onRead(While)" + _wpos.ToString()+"  "+_rpos.ToString());
                Debug.Log("_onRead(While) _read=" + _read.ToString());
                for (int i = 0; i < 11;i++ )
                {
                    Debug.Log("_onRead(While) _read:" + i.ToString()+"->"+_read[i].ToString());
                }
                
                int size = _wpos - _rpos;
                System.Diagnostics.Debug.Assert(size >= 0);
                if (size < 6) { break; /* no head in the apcket, let's wait.*/ }
                
                // head: size(u16)+code(u32)
                UInt16 packetSize = BitConverter.ToUInt16( _read, (int)_rpos);
                if (packetSize < 4) { Debug.LogError("packetSize<4!!"); break;}

                packetSize = (UInt16)(packetSize - 4);
                if (size < packetSize + S2C_PACK_HEAD_SIZE) { break;/*we have a fragmented apcket. wait fot the complete one before proceeding*/        }
                Opcodes code = (Opcodes)BitConverter.ToUInt32(_read, (int)_rpos + MESSAGEHEAD_SIZE_LENGTH);

                WorldPack Packet = new WorldPack(code, packetSize );
                Packet.append(_read, _rpos + S2C_PACK_HEAD_SIZE, packetSize); // 将缓存中，从当前_rpos + 包头的数据给WorldPack.
           
                // 纪录发包either.
                // LogPacketPrintf(mSize, static_cast<uint16>(mOpcode), mSize ? Packet->contents() : NULL, 0, 0);
                _rpos += (UInt16)(packetSize + S2C_PACK_HEAD_SIZE);

                if (Packet.opcode() == Opcodes.SMSG_PONG)
                {
                    _handlePong(Packet);
                }
                else if (null != _packHandler)
                {
                    // push into a packet array.
                    addEvent(Packet);
                }
                
            }
   
            // copy the left data to the top.
            if (_wpos > _rpos)
            {
                Array.Copy(_read, _rpos, _read, 0, _wpos - _rpos);
            }

            _wpos -= _rpos; // _wpos == _read.getLenth(0);
            _rpos = 0;
            Debug.Log("_onRead(While)  end");
            System.Diagnostics.Debug.Assert(_netStream != null);
            if (true == _tcpClient.Connected)
            {
                Debug.Log("_onRead to  _onRead");

                _netStream.BeginRead(
                _read,
                (int)_wpos,
                (int)(_read.Length - _wpos),
                new AsyncCallback(_onRead),
                null);

                Debug.Log("_onRead to  _onRead2");
            }

            // do a mess packets read to test this code.
        }

        bool m_pause = false;

        public void pause(bool bPause)
        {
            m_pause = bPause;
        }

        public void update()
        {
            if (m_pause)
            {
                return;
            }
            //
            lock(_events)
            {
                if(_packHandler !=null)
                {
                    foreach (WorldPack Packet in _events)
                        _packHandler.onPacket(Packet);
                    //
                    _events.Clear();
                }
            }
           
        }

        public WorldPack getPacket(Opcodes opcode)
        {
            return getPacket(opcode, 10);
        }

        public WorldPack getPacket(Opcodes opcode,float t)
        {
            float time = Time.realtimeSinceStartup + t;
            while (true)
            {
                lock (_events)
                {
                    for (int i = 0; i < _events.Count; i++)
                    {
                        if (_events[i].opcode() == opcode)
                        {
                            WorldPack pack = _events[i];
                            _events.RemoveAt(i);
                            //
                            return pack;
                        }
                    }
                    if (Time.realtimeSinceStartup > time)
                    {
                        _missedEvents.Add(opcode);
                        Debug.LogWarning("miss event: "+opcode+", missed events count: "+_missedEvents.Count);
                        return null;
                    }
                }
            }
            //
            return null;
        }

        // ping pong stuff
        public UInt32 _latencey = 0;  // latencey for last ping.
        public UInt32 _ping = 0;      // pingID this time.
        public UInt32 _lastPing = (UInt32)DateTime.UtcNow.Millisecond; // the time record this ping.        
        public bool _pinAck = true; // is this ping action has been responsed.
        //private Dictionary<int, int> _lastPing = new Dictionary<int, int>();
		
		public void SendPing()
		{
            // unless we got the last ping msg back, or we wont do this ping action agian.
            UInt32 now = (UInt32)DateTime.UtcNow.Millisecond;
            if (!_pinAck)
            {
                Console.WriteLine("     Sending failed."
                +"did not get ack for ping id : {0} \n"
                +"which sent in sec: {1} \n"
                +"           now is: {2} \n"
                +"      latencey is: {3} \n"
                    ,_ping
                    ,_lastPing
                    , now
                    , _latencey);
                return;
            }

            System.Random ro = new System.Random();
            _ping = (UInt32)ro.Next(0, 60000);
            _lastPing = now;
            _pinAck = false;

			WorldPack pack = new WorldPack(Opcodes.CMSG_PING,100+2*sizeof(UInt32));
            pack.W( (UInt32)_ping);
            pack.W( (UInt32)_latencey); // this is calculate on last pong.                        
			OutPacket (pack);            
		}

        private void _handlePong(WorldPack pack)
        {            
            UInt32 rec_ping = 0;
            UInt32 now = (UInt32)DateTime.UtcNow.Millisecond;
            pack.R(ref rec_ping);
            if (rec_ping != _ping)
            {
                Console.WriteLine("sending : we look for get ping: {0},but get ping: {1} on time: {2}"
                , _ping
                , rec_ping
                , now);
                _pinAck = true;
                return;
            }

            _latencey = (UInt32)(now - _lastPing);
            _pinAck = true;
        }

        // regist handler to handle packetes.
        private Handler _packHandler = null;
        public void setHandler(Handler h)
        {
            //Debug.Log("####################### setHandler: "+h);
            _packHandler = h;
        }
	}

}