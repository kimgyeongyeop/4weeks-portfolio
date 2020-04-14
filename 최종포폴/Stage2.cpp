#include "stdafx.h"
#include "Stage2.h"


Stage2::Stage2()
{
}


Stage2::~Stage2()
{
}

HRESULT Stage2::init()
{
	SOUNDMANAGER->play("배경음악", 6);
	DATA->playerInfo.currentmapindex = 3;
	_MAP = IMAGEMANAGER->findImage("스테이지2");
	CAMERAMANAGER->set_CameraWorldSize(2000, 1400);


	

	maprc[0].rc = RectMake(0, 1256, 784, 100);
	maprc[1].rc = RectMake(1310, 1256, 687, 100);
	maprc[2].rc = RectMake(788, 981, 520, 100);

	maprc[3].rc = RectMake(737, 740, 626, 20);
	maprc[4].rc = RectMake(376, 513, 1335, 20);
	maprc[5].rc = RectMake(740, 282, 622, 20);

	rightmaprc[0].rc = RectMake(1288, 983, 20, 300);
	leftmaprc[0].rc = RectMake(788, 982, 20, 300);
	DATA->playerInfo.locationX = 1020;
	DATA->playerInfo.locationY = 160;
	AllMap::init();

	bg[0] = IMAGEMANAGER->findImage("맑은하늘");
	bg[1] = IMAGEMANAGER->findImage("배경4");

	MonsterMG->set_BasicMonster({ 100,1153 });
	MonsterMG->set_BasicMonster({ 300,1153 });
	MonsterMG->set_BasicMonster({ 400,1153 });
	MonsterMG->set_BasicMonster({ 1774,1153 }); //103
	MonsterMG->set_BasicMonster({ 1800,1153 });
	MonsterMG->set_BasicMonster({ 1900,1153 });
	MonsterMG->set_FlowerMonster({ 1600,420 });  //93
	MonsterMG->set_FlowerMonster({ 530,420 });
	MonsterMG->set_PicoloMonster({ 810,890 });
	MonsterMG->set_PicoloMonster({ 890,890 });

	MonsterMG->set_PicoloMonster({ 100,1153 });
	MonsterMG->set_PicoloMonster({ 150,1153 });
	MonsterMG->set_PicoloMonster({ 300,1153 });

	MonsterMG->set_PicoloMonster({ 1774,1153 });  //103
	MonsterMG->set_PicoloMonster({ 1800,1153 }); 
	MonsterMG->set_PicoloMonster({ 1900,1153 });

	MonsterMG->set_PoisonMonster({ 985,650 });  
	MonsterMG->set_PirateMonster({ 918,270 });  //243
	/*MonsterMG->set_GetAngleMonster({ 1350,2080 });
	MonsterMG->set_GetAngleMonster({ 1150,2080 });*/

	potalposX = 1500;
	potalposY = 966;
	MonsterMG->setPlayerMemoryAddressLink(player);
	player->setMemoryAddressLink(MonsterMG);

	blocktype = 0;
	return S_OK;
}

void Stage2::release()
{
}

void Stage2::update()
{
	AllMap::update();
	MonsterAndMapCollion(6);
	PlayerAndMapCollion(6, 1, 1);
	//MakePotalCollison("스테이지3");
	MakePotalCollison();
}

void Stage2::render()
{


	//background->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	for (int i = 0; i < 2; ++i)
	{

		bg[i]->loopRender(CAMERAMANAGER->getWorldDC(), &RectMake(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY), CAMERAMANAGER->get_CameraX()*i*0.5f, CAMERAMANAGER->get_CameraY());
	}

	/*GroundRectRender(6);
	LeftRectRender(1);
	RightRectRender(1);*/
	AllMap::render();

	
}

