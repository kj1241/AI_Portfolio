#include "stdafx.h"

IdleState::IdleState():pPlayer(nullptr), wX(0),wY(0)
{
}

IdleState::~IdleState()
{
}

void IdleState::Enter(Entity * entity)
{
	cout<< "플레이어가 몬스터를 찾습니다." << endl;
}

void IdleState::Execute(Entity * entity)
{
	if (NULL == entity)
		return;

	pPlayer = (Player*)entity;
	wX= pPlayer->GetX();
	wY = pPlayer->GetY();

	if (wX - pPlayer->GetX() < 3 && wY - pPlayer->GetY() < 3)
	{
		State* pState = pPlayer->GetState(Move);
		if (NULL != pState)
		{
			pPlayer = (Player*)entity;
			pPlayer->SetState(pState);
			pState->Enter(pPlayer);
		}
	}
}

void IdleState::Exit(Entity * entity)
{
}
