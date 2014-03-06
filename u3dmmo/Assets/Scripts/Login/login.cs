using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;
public class login : MonoBehaviour {
    //public GameObject btnLogin;
    //public List<EventDelegate> testevent = new List<EventDelegate>();

    public UIInput inputIP;
    public UIInput inputPort;
    public UIInput inputAccout;
    public UIInput inputPwd;
    public UIInput inputChat;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void LoginIn()
    {
        Debug.Log("now login...");
        //Application.LoadLevel("main");
        //EventDelegate.Execute(testevent);

        Main.SendLogin(inputIP.text, Convert.ToInt32(inputPort.text), inputAccout.text, inputPwd.text);
    }

    public void haha()
    {
        Debug.Log("haha");
    }

    public void SendChat()
    {
        Main.SendChat(7,inputChat.text);
    }
}
