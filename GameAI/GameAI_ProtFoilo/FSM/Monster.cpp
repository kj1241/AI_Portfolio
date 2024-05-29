#include "stdafx.h"

Monster::Monster()
{
	//위치, hp
	X = 3;
	Y = 3;
	wHP = 5;
}

Monster::~Monster()
{
}

void Monster::MonsterDead()
{
	cout << "몬스터가 죽음~!" << endl;
}
