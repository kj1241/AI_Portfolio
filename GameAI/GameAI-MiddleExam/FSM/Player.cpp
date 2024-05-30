#include "stdafx.h"

Player::Player(): pState(NULL), pEnemy(NULL), stateID(Init) 
{
	//플레이어 위치
	X = 0;
	Y = 2;
	wHP = 5;

	wID = Init;


	pAttackState = new AttackState();
	pIdleState = new IdleState();
	pMoveState = new MoveState();
	pReturnState = new ReturnState();


	stateMap.SetAt(Init, (State*)pIdleState);
	stateMap.SetAt(Move, (State*)pMoveState);
	stateMap.SetAt(Attack, (State*)pAttackState);
	stateMap.SetAt(Return, (State*)pReturnState);

	pState = pIdleState;

}

Player::~Player()
{
	pos = stateMap.GetStartPosition();
	while (pos)
	{
		State* pState = NULL;
		stateMap.RemoveAtPos(pos);
		pState = stateMap.GetNextValue(pos);

		if (NULL != pState)
		{
			delete pState;
			pState = NULL;
		}
	}

}

void Player::Update()
{
	if (NULL != pState)
		pState->Execute(this);
}

State * Player::GetState(WORD wStateID)
{
	pState = NULL;
	if (stateMap.Lookup(wStateID, pState))
		return pState;

	return NULL;
}

void Player::SetState(State * pState)
{
	this->pState = pState;
}

State * Player::GetState()
{
	return pState;
}



void Player::SetEnemy(Entity * pEntity)
{
	this->pEnemy = pEntity;
}

Entity * Player::GetEnemy()
{
	return pEnemy;
}
