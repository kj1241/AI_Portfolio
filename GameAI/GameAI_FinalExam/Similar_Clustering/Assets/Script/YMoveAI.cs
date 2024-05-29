using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class YMoveAI : MonoBehaviour
{
    Vector3 CurrtPoistion;
    Vector3 goPosion;

    // Start is called before the first frame update
    void Start()
    {
        CurrtPoistion = gameObject.transform.position;
        goPosion = Vector3.forward;

    }

    // Update is called once per frame
    void Update()
    {
        if (gameObject.transform.position.z >= -2 || gameObject.transform.position.z <= -7)
            goPosion = -goPosion;



        gameObject.transform.Translate(goPosion * 3 * Time.deltaTime);

    }
}
