﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class L3fight : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
    void OnTriggerStay(Collider col)
    {
        if (col.gameObject.tag == "Leader1")
        {
            soldder3_move.isFight = true;
        }

    }
    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.tag == "Leader1")
        {
            soldder3_move.isFight = false;
        }
    }
}
