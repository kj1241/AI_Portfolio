#ifndef IDLESTATE_H
#define IDLESTATE_H

class Player;

class IdleState : public State
{
private:
	Player * pPlayer;
	WORD wX;
	WORD wY;
public:
	IdleState();
	~IdleState();
	void Enter(Entity* entity);
	void Execute(Entity* entity);
	void Exit(Entity* entity);
};


#endif // !IDLESTATE_H
