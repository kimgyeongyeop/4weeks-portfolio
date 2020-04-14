#include "stdafx.h"
#include "Stage4.h"


Stage4::Stage4()
{
}


Stage4::~Stage4()
{
}

HRESULT Stage4::init()
{
	SOUNDMANAGER->play("¹è°æÀ½¾Ç", 6);
	DATA->playerInfo.currentmapindex = 5;
	_MAP = IMAGEMANAGER->findImage("½ºÅ×ÀÌÁö4");
	CAMERAMANAGER->set_CameraWorldSize(3500, 1300);


	


	maprc[0].rc = RectMake(0, 522, 1704, 100);
	maprc[1].rc = RectMake(1845, 630, 471, 20);
	maprc[2].rc = RectMake(1845, 871, 471, 20);
	
	maprc[3].rc = RectMake(1440, 1155, 2060, 20);
	maprc[4].rc = RectMake(2599, 723, 840, 20);
	

	
	rightmaprc[0].rc = RectMake(1685, 531, 20, 250);
	rightmaprc[1].rc = RectMake(1422, 775, 20, 500);

	DATA->playerInfo.locationX = 50;
	DATA->playerInfo.locationY = 400;
	AllMap::init();
	bg[0] = IMAGEMANAGER->findImage("¸¼ÀºÇÏ´Ã");
	bg[1] = IMAGEMANAGER->findImage("¹è°æ4");

	MonsterMG->set_BasicMonster({ 300,419 });
	MonsterMG->set_BasicMonster({ 500,419 });
	MonsterMG->set_BasicMonster({ 1200,419 });
	MonsterMG->set_PicoloMonster({ 1100,419 });
	MonsterMG->set_PicoloMonster({ 1000,419 });

	
	MonsterMG->set_FlowerMonster({ 1400 ,429 });
	MonsterMG->set_FlowerMonster({ 2000,537 });

	MonsterMG->set_PirateMonster({ 1900,628 });

	MonsterMG->set_PoisonMonster({ 650,444 });
	MonsterMG->set_PoisonMonster({ 1200,444 });

	MonsterMG->set_GetAngleMonster({ 2700,622 }); //101
	//MonsterMG->set_GetAngleMonster({ 2800,622 });
	MonsterMG->set_GetAngleMonster({ 1900,770 });

	MonsterMG->set_BasicMonster({ 1600,1052 });
	MonsterMG->set_BasicMonster({ 1800,1052 });
	MonsterMG->set_BasicMonster({ 2000,1052 });
	MonsterMG->set_BasicMonster({ 2500,1052 });
	MonsterMG->set_BasicMonster({ 2800,1052 });
	MonsterMG->set_BasicMonster({ 3000,1052 });
	MonsterMG->set_PicoloMonster({ 2800,1052 });
	MonsterMG->set_PicoloMonster({ 2500,1052 });

	MonsterMG->set_PicoloMonster({ 2700,620 });
	MonsterMG->set_PicoloMonster({ 2800,620 });
	MonsterMG->set_PicoloMonster({ 3000,620 });
	blocktype = 0;
	potalposX = 3180;
	potalposY = 855;
	
	return S_OK;
}

void Stage4::release()
{
	
}

void Stage4::update()
{
	AllMap::update();
	CheakLocation();
	MonsterAndMapCollion(5);
	PlayerAndMapCollion(5, 0, 2);
	MakePotalCollison();
}

void Stage4::render()
{
	//background->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	for (int i = 0; i < 2; ++i)
	{

		bg[i]->loopRender(CAMERAMANAGER->getWorldDC(), &RectMake(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY), CAMERAMANAGER->get_CameraX()*i*0.5f, CAMERAMANAGER->get_CameraY());
	}

	//GroundRectRender(6);
	//LeftRectRender(0);
	//RightRectRender(2);
	AllMap::render();

	
}
