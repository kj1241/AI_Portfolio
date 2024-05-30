#ifndef PLAYER_H
#define PLAYER_H

#include <atlcoll.h>

class State;
class AttackState;
class IdleState;
class MoveState;
class ReturnState;

//상태
enum State_Entity
{
	Init = 0,
	Move = 1,
	Attack = 2,
	Return = 3,
	Dead = 4
};

//플레이어
class Player: public Entity
{
private:
	CAtlMap<WORD, State*> stateMap;
	State* pState;
	Entity* pEnemy;
	State_Entity stateID;
	POSITION pos;

public:
	Player();
	~Player();
	void Update();
	State* GetState(WORD wStateID);
	void SetState(State* pState);
	State* GetState(); 
	void SetEnemy(Entity* pEntity);
	Entity* GetEnemy();

	AttackState* pAttackState;
	IdleState* pIdleState;
	MoveState* pMoveState;
	ReturnState* pReturnState ;


};


#endif