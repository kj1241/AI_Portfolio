using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Unity.MLAgents;
using Unity.MLAgents.Sensors;

public class RollerAgent : Agent
{
    Rigidbody rBody;
    public Transform Target;
    public float speed = 10;
    void Start()
    {
        rBody = GetComponent<Rigidbody>();
    }
   //머신러닝 시작할때 조건
    public override void OnEpisodeBegin()
    {
        //떨어졌을때 조건
        if (this.transform.localPosition.y < 0)
        {
            this.rBody.angularVelocity = Vector3.zero;
            this.rBody.velocity = Vector3.zero;
            this.transform.localPosition = new Vector3(0, 0.5f, 0);
        }
        //타겟위치 조건
        Target.localPosition = new Vector3(Random.value * 8 - 4,  0.5f,  Random.value * 8 - 4);
    }

    //센서 연결.
    public override void CollectObservations(VectorSensor sensor)
    {
        sensor.AddObservation(Target.localPosition);
        sensor.AddObservation(this.transform.localPosition);

        sensor.AddObservation(rBody.velocity.x);
        sensor.AddObservation(rBody.velocity.z);
    }



    public override void OnActionReceived(float[] vectorAction)
    {
        //초기화
        Vector3 controlSignal = Vector3.zero;

        //움직이는 방법
        controlSignal.x = vectorAction[0];
        controlSignal.z = vectorAction[1];

        //속도 넣기
        rBody.AddForce(controlSignal * speed);

        //거리확인
        float distanceToTarget = Vector3.Distance(this.transform.localPosition, Target.localPosition);

        //보상조건
        if (distanceToTarget < 1.42f)
        {
            SetReward(1.0f);
            EndEpisode();
        }

        //초기화 조건
        if (this.transform.localPosition.y < 0)
        {
            EndEpisode();
        }
    }


    //휴리스틱
    public override void Heuristic(float[] actionsOut)
    {
        actionsOut[0] = Input.GetAxis("Horizontal");
        actionsOut[1] = Input.GetAxis("Vertical");
        Debug.Log("a");
    }

}
