using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class soldder3_move : MonoBehaviour {

    public static bool isFight = false;

    public GameObject Leader;
    public float MOVE_SPEED = 5.0f;
    public bool bMove = true;
    public bool Crash = false;
    Vector3 move_vector = Vector3.zero;
    Vector3 temp_vector = Vector3.zero;

    // Use this for initialization
    void Start()
    {
        Leader = GameObject.Find("Leader3");

    }

    // Update is called once per frame
    void Update()
    {
        if (isFight == false)
        {
            if (bMove == true)
            {
                move_vector = Leader.transform.position - gameObject.transform.position;
                move_vector.Normalize();
                move_vector *= MOVE_SPEED * Time.deltaTime;
                transform.Translate(move_vector);
                //gameObject.transform.position = gameObject.transform.position + move_vector;
            }
            if (Crash == true && bMove == false)
            {
                temp_vector.Normalize();
                temp_vector *= MOVE_SPEED * Time.deltaTime;
                transform.Translate(temp_vector);
            }
        }

        if (isFight == true)
        {
            gameObject.transform.position = Leader.transform.position;
        }

    }

    public bool isbMove()
    {
        return bMove;
    }





    void OnTriggerStay(Collider col)
    {
        if (col.gameObject == Leader)
        {
            if (isFight == false)
            {
                bMove = false;
            }

        }
        if (col.gameObject.tag == "soldier3")
        {
            if (isFight == false)
            {
                Vector3 temp_vector2 = Vector3.zero;
                Crash = true;
                temp_vector2 = gameObject.transform.position - col.transform.position;
                temp_vector2.Normalize();

                temp_vector = temp_vector + temp_vector2;

            }
        }

    }
  
    void OnTriggerExit(Collider other)
    {
        if (other.gameObject == Leader)
        {
            if (isFight == false)
            {
                bMove = true;
            }
        }
        if (other.gameObject.tag == "soldier3")
        {
            if (isFight == false)
            {
                Vector3 temp_vector2 = Vector3.zero;
                Crash = false;
                temp_vector2 = gameObject.transform.position - other.transform.position;
                temp_vector2.Normalize();

                temp_vector = temp_vector - temp_vector2;

            }

        }

    }
}
