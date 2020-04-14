#include "stdafx.h"
#include "Stage3.h"


Stage3::Stage3()
{
}


Stage3::~Stage3()
{
}

HRESULT Stage3::init()
{
	SOUNDMANAGER->play("배경음악", 6);
	DATA->playerInfo.currentmapindex = 4;
	_MAP = IMAGEMANAGER->findImage("스테이지3");
	CAMERAMANAGER->set_CameraWorldSize(3500, 1300);


	


	maprc[0].rc = RectMake(0, 789, 653, 100);
	maprc[1].rc = RectMake(656, 974, 397, 100);
	maprc[2].rc = RectMake(1048, 1206, 393, 100);

	maprc[3].rc = RectMake(1440, 973, 391, 100);
	maprc[4].rc = RectMake(1833, 1205, 393, 100);
	maprc[5].rc = RectMake(2226, 971, 1273, 100);

	maprc[6].rc = RectMake(967, 680, 1208, 20);
	maprc[7].rc = RectMake(967, 441, 1208, 20);

	rightmaprc[0].rc = RectMake(636, 798, 20, 250);
	rightmaprc[1].rc = RectMake(1029,978, 20, 250);
	rightmaprc[2].rc = RectMake(1814, 979, 20, 250);
	
	leftmaprc[0].rc = RectMake(1437, 980, 20, 250);
	leftmaprc[1].rc = RectMake(2225, 973, 20, 250);
	DATA->playerInfo.locationX = 110;
	DATA->playerInfo.locationY = 650;
	AllMap::init();
	bg[0] = IMAGEMANAGER->findImage("맑은하늘");
	bg[1] = IMAGEMANAGER->findImage("배경4");
	
	MonsterMG->set_BasicMonster({ 1500,870 });
	MonsterMG->set_BasicMonster({ 1600,870 });
	MonsterMG->set_BasicMonster({ 1650,870 });

	MonsterMG->set_FlowerMonster({ 2300,878 });  //93
	MonsterMG->set_FlowerMonster({ 2500,878 });

	MonsterMG->set_PicoloMonster({ 1200,577 });
	MonsterMG->set_PicoloMonster({ 1000,338 });
	MonsterMG->set_PicoloMonster({ 1200,338 });
	MonsterMG->set_PicoloMonster({ 1400,338 });
	//MonsterMG->set_FlowerMonster({ 1600,146 });

	MonsterMG->set_PoisonMonster({ 985,600 });
	MonsterMG->set_PoisonMonster({ 1200,600 });
	MonsterMG->set_PoisonMonster({ 1400,600 });

	MonsterMG->set_PirateMonster({ 1500,437 });
	MonsterMG->set_PirateMonster({ 1500,198 });//243

	//MonsterMG->set_GetAngleMonster({ 1350,2080 });
	
	trapimg[0]= IMAGEMANAGER->findImage("가시");
	trapimg[1]= IMAGEMANAGER->findImage("가시");
	traprc[0] = RectMake(1047, 1130, trapimg[0]->getWidth(), trapimg[0]->getHeight());
	traprc[1] = RectMake(1833, 1130, trapimg[0]->getWidth(), trapimg[0]->getHeight());
	blocktype = 0;
	potalposX = 3180;
	potalposY = 688;
	istraprender = true;
	return S_OK;
}

void Stage3::release()
{

}

void Stage3::update()
{
	AllMap::update();
	MonsterAndMapCollion(8);
	//땅 , 벽기준 왼쪽 , 벽기준오른쪽
	PlayerAndMapCollion(8, 2, 3);

	//MakePotalCollison("스테이지4");
	MakePotalCollison();
}

void Stage3::render()
{

	//background->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	for (int i = 0; i < 2; ++i)
	{

		bg[i]->loopRender(CAMERAMANAGER->getWorldDC(), &RectMake(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY), CAMERAMANAGER->get_CameraX()*i*0.5f, CAMERAMANAGER->get_CameraY());
	}
	/*GroundRectRender(8);
	LeftRectRender(2);
	RightRectRender(3);*/
	AllMap::render();

}
