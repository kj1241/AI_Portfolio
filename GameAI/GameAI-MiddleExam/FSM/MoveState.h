#ifndef MOVESTATE_H
#define MOVESTATE_H

class Player;

class MoveState : public State
{
private:
	Player * pPlayer;
	WORD wX;
	WORD wY;
public:
	MoveState();
	void Enter(Entity* entity);
	void Execute(Entity* entity);
	void Exit(Entity* entity);
};

#endif