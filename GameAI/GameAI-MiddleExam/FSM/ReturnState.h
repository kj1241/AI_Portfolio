#ifndef RETURNSTATE_H
#define RETURNSTATE_H



class Player;

//∏Æ≈œ
class ReturnState : public State
{
public:
	ReturnState();
	~ReturnState();
	void Enter(Entity* entity);
	void Execute(Entity* entity);
	void Exit(Entity* entity);
};



#endif