using UnityEngine;
using System.Collections;

public class uipublic : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public delegate void VoidDelegate(GameObject go);
    public static void RegButonClickEvent(GameObject button, UIEventListener.VoidDelegate fun)
    {
        //GameObject button = GameObject.Find(objName);
        if (button != null)
        {
            UIEventListener.Get(button).onClick = fun;
        }
    }
}
