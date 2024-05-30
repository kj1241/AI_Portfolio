#include "stdafx.h"

//메인루프
void main()
{
	Player* pPlayer = new Player(); //플레이어
	Monster* pMonster = new Monster(); //몬스터
	pPlayer->SetEnemy(pPlayer); 

	//업데이트
	while (true)
	{
		pPlayer->Update(); //플레이어 업데이트
		Sleep(500);
	}
	
}