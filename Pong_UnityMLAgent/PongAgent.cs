
using UnityEngine;
using Unity.MLAgents;
using Unity.MLAgents.Sensors;

public class PongAgent : Agent
{
    public GameObject Ball;
    public GameObject Opponent;
    private Rigidbody RbBall;
    private Rigidbody RbAgent;
    private Rigidbody RbOpponent;
    private const int Stay = 0;
    private const int Up = 1;
    private const int Down = 2;
    Vector3 ResetPos;


    void Start()
    {
        RbAgent = GetComponent<Rigidbody>();
        RbOpponent = Opponent.GetComponent<Rigidbody>();
        RbBall = Ball.GetComponent<Rigidbody>();
        //자신의 기본 포지션 지정
        ResetPos = transform.position;
    }
   /*
    private void Update()
    {
        float a =Input.GetAxis("Vertical");
        Vector3 position = transform.position;
        position.x += a * Time.deltaTime*5;
        transform.position = position;
    }
   */
    //센서 연결.
    public override void CollectObservations(VectorSensor sensor)
    {
        //신경망
        sensor.AddObservation(transform.position.x);
        sensor.AddObservation(transform.position.z);

        sensor.AddObservation(Opponent.transform.position.x);
        sensor.AddObservation(Opponent.transform.position.z);

        sensor.AddObservation(Ball.transform.position.x);
        sensor.AddObservation(Ball.transform.position.z);

        sensor.AddObservation(RbAgent.velocity.x);
        sensor.AddObservation(RbAgent.velocity.z);

        sensor.AddObservation(RbBall.velocity.x);
        sensor.AddObservation(RbBall.velocity.z);

    }

    public override void OnActionReceived(float[] vectorAction)
    {
      
        
        int action = Mathf.FloorToInt(vectorAction[0]);
        switch(action)
        {
            case Stay:
                //에이전트의 현재 좌표를 그대로 유지
                this.transform.position = this.transform.position + 0f * Vector3.right;
                break;

            case Up:
                //현재 좌표를 유니티 좌표축 오른쪽만큼 이동
                this.transform.position = this.transform.position + 0.3f * Vector3.right;
                break;

            case Down:
                //현재 좌표를 유니티 좌표축 오른쪽만큼 이동
                this.transform.position = this.transform.position + 0.3f * Vector3.left;
                break;

        }
        



    }

    public override void OnEpisodeBegin()
    {
        //초기화 일딴 더 생각해보자.
        transform.position = ResetPos;
        // Ball.GetComponent<PongGoalDetection>().ResetPosition();


    }

    public void OpponenwtScored()
    {
        AddReward(-1f);
        EndEpisode();
    }
    public void ScoredGoal()
    {
        AddReward(1f);
        EndEpisode();
    }

    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.GetComponent("Wall"))
        {
            RbAgent.velocity = Vector3.zero;
            RbAgent.angularVelocity = Vector3.zero;
            
        }
        if (collision.gameObject.CompareTag("Ball"))
        {
            AddReward(0.5f);
        }
    }

    public override void Heuristic(float[] actionsOut)
    {
        // 테스트할때 필요한 용이기 때문
        /*
        if (Input.GetKeyDown(KeyCode.A))
        {
            actionsOut[0] = RbAgent.position.z + 1f;

            Debug.Log("a");
        }
      */
       

    }





}
