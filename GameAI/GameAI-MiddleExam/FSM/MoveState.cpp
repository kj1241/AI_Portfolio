#include "stdafx.h"

MoveState::MoveState()
{
}

void MoveState::Enter(Entity * entity)
{
	cout << "플레이어가 몬스터한테 갑니다." << endl;
}

void MoveState::Execute(Entity * entity)
{
	if (NULL == entity)
		return;

	pPlayer = (Player*)entity;
	wX= pPlayer->GetX();
	wY = pPlayer->GetY();
	if (PLAYER_POS_X != wX)
		pPlayer->SetX(wX+1);

	if (PLAYER_POS_Y != wY)
		pPlayer->SetY(wY+1);

	cout << "Monster이동 중 x:"<<wX<<"y:"<< wY<< endl<<" Player 위지 x:"<<PLAYER_POS_X<<"y:"<<PLAYER_POS_Y << endl;

	if (PLAYER_POS_X == wX && PLAYER_POS_Y == wY)
	{
		State* pState = pPlayer->GetState(Attack);
		if (NULL != pState)
		{
			pPlayer->SetState(pState);
			pState->Enter(pPlayer);
		}
	}
}


void MoveState::Exit(Entity * entity)
{
}
