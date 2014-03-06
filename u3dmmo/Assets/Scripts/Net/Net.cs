using UnityEngine;
using System.Collections;
using AssemblyCSharp;

public class Net : MonoBehaviour {

    const string KEY_SERVER_IP = "ServerIP";
    const string KEY_SERVER_Port = "ServerPort";
    static string s_serverIP = "";
    static int s_serverPort = 7200;
    public static string getServerIP()
    {
        if (Application.platform == RuntimePlatform.WindowsEditor || Application.platform == RuntimePlatform.OSXEditor)
        {
            return s_serverIP;
        }
        else
        {
            return "127.0.0.1";
        }
    }
	 
	public static int getServerPort()
    {
        if (Application.platform == RuntimePlatform.WindowsEditor || Application.platform == RuntimePlatform.OSXEditor )
        {
            return s_serverPort;
        }
        else
        {
			return 7200;
        }
    }

    public static void saveServerIP(string ip)
    {
        s_serverIP = ip;
        PlayerPrefs.SetString(KEY_SERVER_IP, s_serverIP);
    }

    public static void loadServerIP()
    {
        s_serverIP = PlayerPrefs.GetString(KEY_SERVER_IP, "222.73.21.72");
    }
    public static void saveServerPort(int port)
    {
        s_serverPort = port;
        PlayerPrefs.SetInt(KEY_SERVER_Port, s_serverPort);
    }

    public static void loadServerPort()
    {
        s_serverPort = PlayerPrefs.GetInt(KEY_SERVER_Port, 8093);
    }

    public static Socket s_loginSocket = new Socket();
    public static gcSocket s_gcSocket = new gcSocket();

    static bool s_useNet = false;

    public static void setUseNet()
    {
        s_useNet = true;
    }

    public static bool isUseNet()
    {
        return s_useNet;
    }

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
