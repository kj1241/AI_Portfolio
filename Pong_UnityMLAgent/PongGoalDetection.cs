using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PongGoalDetection : MonoBehaviour
{
    public PongAgent AgentA;
    public PongAgent AgentB;
    private Rigidbody RbBall;
    Vector3 ResetPos;
    Vector3 velocity;
    private float max_ball_speed=10f;
    private float min_ball_speed=5f;



    // Start is called before the first frame update
    void Start()
    {      
        RbBall = GetComponent<Rigidbody>();
        ResetPos = transform.position;
        ResetPosition();

    }

    // Update is called once per frame
    void Update()
    {
      
    }
    public void ResetPosition()
    {
        transform.position = ResetPos;
        RbBall.velocity = Vector3.zero;
        transform.rotation = Quaternion.identity;

        float rand_num = Random.Range(-1f, 1f);

        if(rand_num<-0.5f)
            velocity = new Vector3(Random.Range(min_ball_speed, max_ball_speed), 0, Random.Range(min_ball_speed, max_ball_speed));

        else if (rand_num<0f)
            velocity = new Vector3(Random.Range(min_ball_speed, max_ball_speed), 0, Random.Range(-max_ball_speed, -min_ball_speed));
       
        else if (rand_num < 0.5f)
            velocity = new Vector3(Random.Range(-max_ball_speed, -min_ball_speed), 0, Random.Range(min_ball_speed, max_ball_speed));
       
        else 
            velocity = new Vector3(Random.Range(-max_ball_speed, -min_ball_speed), 0, Random.Range(-max_ball_speed, -min_ball_speed));


        RbBall.AddForce(velocity);


    }

    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.CompareTag("GoalA"))
        {
            ResetPosition();
            AgentB.ScoredGoal();
            AgentA.OpponenwtScored();
            AgentA.EndEpisode();
            AgentB.EndEpisode();
    

        }

        if (collision.gameObject.CompareTag("GoalB"))
        {
            ResetPosition();
            AgentA.ScoredGoal();
            AgentB.OpponenwtScored();
            AgentA.EndEpisode();
            AgentB.EndEpisode();
     

        }
    }

    




}
