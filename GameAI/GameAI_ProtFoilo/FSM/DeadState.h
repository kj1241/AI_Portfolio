#ifndef DEADSTATE_H
#define DEADSTATE_H



class Player;

class DeadState : public State
{
public:
	DeadState();
	~DeadState();
	void Enter(Entity* entity);
	void Execute(Entity* entity);
	void Exit(Entity* entity);
};

#endif