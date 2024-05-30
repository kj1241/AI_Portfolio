using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class solder1 : MonoBehaviour {

    public int soilderNumber=6;
    public GameObject prefab;

    
    // Use this for initialization
    void Start () {
		for(int i=0; i< soilderNumber; i++)
        {
            float x = Random.Range(-20.0f, 20.0f);
            float z = Random.Range(-20.0f, 20.0f);
            Instantiate(prefab, new Vector3(x, 1, z), Quaternion.identity);
        }
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
