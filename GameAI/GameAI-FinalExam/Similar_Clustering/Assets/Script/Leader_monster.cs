using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Leader_monster : MonoBehaviour
{
   public Color m = Color.red;

    Renderer capsuleColor;
    // Start is called before the first frame update
    void Start()
    {
        capsuleColor = gameObject.GetComponent<Renderer>();
    }

    // Update is called once per frame
    void Update()
    {
        capsuleColor.material.color = m;
    }
}
