using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class seletColor : MonoBehaviour
{
    enum ColorState {none,red,blue,green};

    ColorState colorState= ColorState.none;
    float distance = -1f;

    Renderer capsuleColor;
    Vector3 tempPosition = new Vector3(0, 0, 0);

    bool isToLeaderMoving = false;

    // Start is called before the first frame update
    void Start()
    {
        capsuleColor = gameObject.GetComponent<Renderer>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }




    
    private void OnTriggerStay(Collider other)
    {

        if (other.tag == "red")
        {   
            if(colorState!= ColorState.red)
            {
                if(distance>Vector3.Distance(other.transform.position,this.transform.position) || distance == -1f)
                {
                    colorState = ColorState.red;
                    distance = Vector3.Distance(other.transform.position, this.transform.position);
                    capsuleColor.material.color = Color.red;
                    tempPosition = other.transform.position;
                    isToLeaderMoving = true;


                }

            }
            if(colorState == ColorState.red&& isToLeaderMoving==true)
            {
                distance = Vector3.Distance(other.transform.position, this.transform.position);

                if(distance>3)
                {
                    Vector3 temp = other.transform.position - this.transform.position;

                    gameObject.transform.Translate(temp.normalized * 2 * Time.deltaTime);


                }

                if (distance <= 3)
                {
                    Vector3 temp = this.transform.position- other.transform.position;

                    gameObject.transform.Translate(temp.normalized * 2 * Time.deltaTime);


                }


            }

        }
        if (other.tag == "blue")
        {
            if (colorState != ColorState.blue)
            {
                if (distance > Vector3.Distance(other.transform.position, this.transform.position)|| distance==-1f)
                {
                    colorState = ColorState.blue;
                    distance = Vector3.Distance(other.transform.position, this.transform.position);
                    capsuleColor.material.color = Color.blue;
                    tempPosition = other.transform.position;
                    isToLeaderMoving = true;
                }

            }
            if (colorState == ColorState.blue)
            {
                distance = Vector3.Distance(other.transform.position, this.transform.position);
                if (distance > 3)
                {
                    Vector3 temp = other.transform.position - this.transform.position;

                    gameObject.transform.Translate(temp.normalized * 2 * Time.deltaTime);


                }

                if (distance <= 3)
                {
                    Vector3 temp = this.transform.position - other.transform.position;

                    gameObject.transform.Translate(temp.normalized * 2 * Time.deltaTime);


                }
            }

        }

        if (other.tag == "green")
        {
            if (colorState != ColorState.green)
            {
                

                if (distance > Vector3.Distance(other.transform.position, this.transform.position) || distance == -1f)
                {
                    colorState = ColorState.green;

                    distance = Vector3.Distance(other.transform.position, this.transform.position);
                    capsuleColor.material.color = Color.green;
                    tempPosition = other.transform.position;
                    isToLeaderMoving = true;
                }

            }
            if (colorState == ColorState.green)
            {
                distance = Vector3.Distance(other.transform.position, this.transform.position);
                if (distance > 3)
                {
                    Vector3 temp = other.transform.position - this.transform.position;

                    gameObject.transform.Translate(temp.normalized * 2 * Time.deltaTime);


                }

                if (distance <= 3)
                {
                    Vector3 temp = this.transform.position - other.transform.position;

                    gameObject.transform.Translate(temp.normalized * 2 * Time.deltaTime);


                }
            }

        }


        if (other.tag == "unit")
        {
            if (4 > Vector3.Distance(this.transform.position, other.transform.position))
            {
                

                Vector3 temp = this.transform.position - other.transform.position;

                Debug.Log("temp");


                this.transform.Translate(temp.normalized * 2 * Time.deltaTime);

            }

            if (4 <= Vector3.Distance(this.transform.position, other.transform.position))
            {


                Vector3 temp =  other.transform.position- this.transform.position;

                Debug.Log("temp");


                this.transform.Translate(temp.normalized * 1 * Time.deltaTime);

            }

        }




    }

    private void OnTriggerExit(Collider other)
    {



            colorState = ColorState.none;
            distance = -1;
            capsuleColor.material.color = Color.white;
        



  

    }

    private void OnTriggerEnter(Collider other)
    {

    




    }


  







    //움직이는 방향에 따라 일정하게 움직이기.
    void OtherMovePosition(Collider other)
    {
        if (tempPosition != other.transform.position)
        {
            Vector3 temp = other.transform.position - tempPosition;

            this.transform.Translate(temp.normalized * 2 * Time.deltaTime);
        }

    }

}
