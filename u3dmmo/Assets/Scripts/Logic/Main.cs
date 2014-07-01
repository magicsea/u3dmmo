using UnityEngine;
using System.Collections;
using System;
using AssemblyCSharp;
using System.Collections.Generic;

public struct stloginInfo
{
	public string server_ip;
    public int server_port;
    public string accout;
    public string pwd;
}
public class Main : MonoBehaviour, Handler
{
    static stloginInfo loginInfo;
	// Use this for initialization
	void Start () {
        Debug.Log("Main.Start...");
        Net.s_gcSocket.setHandler(this);
        Net.s_gcSocket.SetConnectCallback(OnConnect);
        DontDestroyOnLoad(gameObject);

	}
	
	// Update is called once per frame
	void Update () {
        Net.s_gcSocket.update();
	}

    void Regist()
    {
        Debug.Log("Main.Regist...");
    }

    public static bool SendLogin(string ip,int port,string account,string pwd)
    {
        loginInfo.server_ip = ip;
        loginInfo.server_port = port;
        loginInfo.accout = account;
        loginInfo.pwd = pwd;

        Debug.Log("SendLogin:" + ip + ":" + port.ToString() + " acc=" + account + " pwd=" + pwd);
        //Net.s_loginSocket.Connect(ip, port);
        Net.s_gcSocket.TryToConnect(ip, port, 5000);
        return true;
    }

    public void OnConnect(bool bSucc)
    {
        Debug.Log("gc=>>>]OnConnect" + bSucc.ToString());
        //login
        WorldPack pk = new WorldPack();
        pk.W((short)1001);
        pk.W(loginInfo.accout);
        pk.W(loginInfo.pwd);
        pk.W((byte)95);
        Net.s_gcSocket.gcOutPacket(pk, false);
    }

    public static void SendChat(byte channel,string say)
    {
        //chat
        Debug.LogWarning("SendChat :" + channel.ToString() + say);
        WorldPack pkChat = new WorldPack();
        pkChat.W((UInt16)1002);
        pkChat.W(channel);
        pkChat.W(say);
        Net.s_gcSocket.gcOutPacket(pkChat, false);
    }

    public void onPacket(WorldPack pack)
    {
        Int16 iCmd = 0;
        pack.R(ref iCmd);
        Debug.LogWarning("onPacket " + iCmd.ToString());
        switch (iCmd)
        {
            case 1001:
                break;
            case 1002:
                {
                    byte channel = 0;
                    pack.R(ref channel);
                    string say="";
                    pack.R(ref say);
                    Debug.LogWarning("onPacket Chat:" + channel.ToString() + "  " + say);
                }
                break;
            default:
                break;
        }
    }
}
