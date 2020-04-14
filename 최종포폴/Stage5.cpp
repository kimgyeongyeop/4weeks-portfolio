#include "stdafx.h"
#include "Stage5.h"


Stage5::Stage5()
{
}


Stage5::~Stage5()
{
}

HRESULT Stage5::init()
{
	SOUNDMANAGER->play("¹è°æÀ½¾Ç", 6);
	DATA->playerInfo.currentmapindex = 6;
	_MAP = IMAGEMANAGER->findImage("½ºÅ×ÀÌÁö5");
	CAMERAMANAGER->set_CameraWorldSize(2500, 1100);


	background = new image;
	background = IMAGEMANAGER->findImage("¹è°æ2");


	maprc[0].rc = RectMake(0, 866, 390, 100);
	maprc[1].rc = RectMake(362, 691, 397, 100);
	maprc[2].rc = RectMake(755, 866, 553, 100);

	maprc[3].rc = RectMake(769, 496, 469, 20);
	maprc[4].rc = RectMake(1305, 323, 396, 100);

	maprc[5].rc = RectMake(1704, 570, 796, 100);
	maprc[6].rc = RectMake(1909, 224, 473, 20);

	rightmaprc[0].rc = RectMake(739, 696, 20, 200);
	rightmaprc[1].rc = RectMake(1681, 330, 20, 300);

	leftmaprc[0].rc = RectMake(360, 703, 20, 200);
	leftmaprc[1].rc = RectMake(1305, 334, 20, 600);
	
	DATA->playerInfo.locationX = 50;
	DATA->playerInfo.locationY = 460;
	AllMap::init();
	bg[0] = IMAGEMANAGER->findImage("¸¼ÀºÇÏ´Ã");
	bg[1] = IMAGEMANAGER->findImage("¹è°æ5");

	maprc[2].rc = RectMake(755, 866, 553, 100);
	MonsterMG->set_GetAngleMonster({ 2000,123 });
	MonsterMG->set_PirateMonster({ 1900,327 });
	MonsterMG->set_PicoloMonster({ 800,763 });
	MonsterMG->set_BasicMonster({ 800,763 });
	MonsterMG->set_BasicMonster({ 900,763 });

	MonsterMG->set_PirateMonster({ 950,253 });

	MonsterMG->set_FlowerMonster({ 1450,237 });
	MonsterMG->set_PoisonMonster({ 1460,250 });
	blocktype = 0;
	potalposX = 2110;
	potalposY = 270;
	return S_OK;
}

void Stage5::release()
{
	
}

void Stage5::update()
{

	AllMap::update();
	MonsterAndMapCollion(7);
	PlayerAndMapCollion(7, 2, 2);
	MakePotalCollison();
}

void Stage5::render()
{

	//background->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	for (int i = 0; i < 2; ++i)
	{

		bg[i]->loopRender(CAMERAMANAGER->getWorldDC(), &RectMake(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY), CAMERAMANAGER->get_CameraX()*i*0.5f, CAMERAMANAGER->get_CameraY());
	}

	/*GroundRectRender(7);
	LeftRectRender(2);
	RightRectRender(2);*/
	AllMap::render();

	
}
