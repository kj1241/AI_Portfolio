using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class XMoveAI : MonoBehaviour
{
    Vector3 CurrtPoistion;
    Vector3 goPosion;


    // Start is called before the first frame update
    void Start()
    {
        CurrtPoistion = gameObject.transform.position;
        goPosion = Vector3.left;
    }

    // Update is called once per frame
    void Update()
    {
        if (gameObject.transform.position.x >= -5 || gameObject.transform.position.x <= -10)
            goPosion = -goPosion;

   

        gameObject.transform.Translate(-goPosion * 3 * Time.deltaTime);
    }

}
