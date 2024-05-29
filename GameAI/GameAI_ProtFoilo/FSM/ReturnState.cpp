#include "stdafx.h"

ReturnState::ReturnState()
{
}

ReturnState::~ReturnState()
{
}

void ReturnState::Enter(Entity * entity)
{
	cout << "플레이어가 원위치로 갑니다." << endl;
}

void ReturnState::Execute(Entity * entity)
{
}

void ReturnState::Exit(Entity * entity)
{
}
