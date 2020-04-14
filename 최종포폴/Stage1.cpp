#include "stdafx.h"
#include "Stage1.h"

#include "Player.h"

Stage1::Stage1()
{
}


Stage1::~Stage1()
{
}

HRESULT Stage1::init()
{
	DATA->playerInfo.currentmapindex = 2;
	SOUNDMANAGER->play("배경음악", 6);
	_MAP = IMAGEMANAGER->findImage("스테이지1");
	CAMERAMANAGER->set_CameraWorldSize(2500, 2500);

	
	
	
	maprc[0].rc = RectMake(0, 258, 1367, 100);
	maprc[1].rc = RectMake(1572, 413, 730, 20);
	maprc[2].rc = RectMake(1572, 726, 730, 20);
	maprc[3].rc = RectMake(2334, 575, 125, 20);
	maprc[4].rc = RectMake(2334, 849, 125, 20);
	maprc[5].rc = RectMake(956, 988, 1544, 100);
	maprc[6].rc = RectMake(554, 865, 260, 20);
	maprc[7].rc = RectMake(554, 1098, 260, 20);
	maprc[8].rc = RectMake(554, 1353, 260, 20);
	maprc[9].rc = RectMake(341, 979, 128, 20);
	maprc[10].rc = RectMake(341,1226, 128, 20);
	maprc[11].rc = RectMake(341, 1475, 128, 20);
	maprc[12].rc = RectMake(241, 1625, 280, 100);
	maprc[13].rc = RectMake(601, 1731, 128, 20);
	maprc[14].rc = RectMake(1011, 1811, 128, 20);
	maprc[15].rc = RectMake(1031, 2011, 128, 20);
	maprc[16].rc = RectMake(524, 1899, 425, 100);
	maprc[17].rc = RectMake(1150, 1683, 1046, 20);
	maprc[18].rc = RectMake(954, 2181, 1550, 100);

	rightmaprc[0].rc = RectMake(1354, 261, 20, 350);
	rightmaprc[1].rc = RectMake(241, 552, 20, 1100);
	rightmaprc[2].rc = RectMake(510, 1632, 20, 500);
	rightmaprc[3].rc = RectMake(932, 1902, 20, 500);
	
	
	background = new image;
	background = IMAGEMANAGER->findImage("배경3");

	DATA->playerInfo.locationX = 50;
	DATA->playerInfo.locationY = 130;
	AllMap::init();

	
	MonsterMG->set_BasicMonster({ 100,158 });
	MonsterMG->set_BasicMonster({ 300,158 });
	MonsterMG->set_BasicMonster({ 1774,312 });
	MonsterMG->set_FlowerMonster({ 1774,310 });
	MonsterMG->set_FlowerMonster({ 1900,310 });
	MonsterMG->set_PicoloMonster({ 1930,310 });
	MonsterMG->set_PicoloMonster({ 1930,630 });
	MonsterMG->set_PoisonMonster({ 1940,650 });
	MonsterMG->set_PirateMonster({ 1350,750 });
	MonsterMG->set_NavyMonster({ 1350,2080 });
	MonsterMG->set_GetAngleMonster({ 1350,2080 }); //101
	MonsterMG->set_GetAngleMonster({ 1150,2080 });
	blocktype = 0;
	potalposX = 2200;
	potalposY = 1891;

	//y축 빼기 290 
	
	return S_OK;
}

void Stage1::release()
{
	//init하기전에 위치설정
	
}

void Stage1::update()
{
	
	AllMap::update();
	// !! 순서중요 몬스터 몬스터 맵 콜리젼이 위에와야함 (ㅇㅇ)
	//MakePotalCollison("스테이지2");
	MakePotalCollison();
	CheakLocation();
	MonsterAndMapCollion(19);
	PlayerAndMapCollion(19, 0, 4);
	
	


	


	


}

void Stage1::render()
{
	

	/*for (int i = 0; i < 2; ++i)
	{
		bg[i]->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	}*/
	background -> render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), 0, 0, WINSIZEX, WINSIZEY);
	//_MAP->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	
	
	/*for (int i = 0; i < 3; ++i)
	{

		bg[i]->loopRender(CAMERAMANAGER->getWorldDC(), &RectMake(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY), CAMERAMANAGER->get_CameraX()*i*0.5f, CAMERAMANAGER->get_CameraY());

		

	}
*/

	/*for (int i = 0; i < 19; ++i)
	{
		Rectangle(CAMERAMANAGER->getWorldDC(), maprc[i].rc);
	}*/
	/*for (int i = 0; i < 4; ++i)
	{
		Rectangle(CAMERAMANAGER->getWorldDC(), rightmaprc[i].rc);
	}*/
	//cout << DATA->playerInfo.playerHP << endl;
	//player->render();
	//MonsterMG->render();

	AllMap::render();

	
	
}



