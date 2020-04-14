#include "stdafx.h"
#include "BossMap.h"


BossMap::BossMap()
{
}


BossMap::~BossMap()
{
}

HRESULT BossMap::init()
{
	DATA->playerInfo.currentmapindex = 9;
	_MAP = IMAGEMANAGER->findImage("∫∏Ω∫Ω∫≈◊¿Ã¡ˆ");
	CAMERAMANAGER->set_CameraWorldSize(2000, 1200);

	maprc[0].rc = RectMake(0, 870, 2000, 100);
	SOUNDMANAGER->play("∫∏Ω∫∏ ¿Ωæ«", 6);
	DATA->playerInfo.locationX = 50;
	DATA->playerInfo.locationY = 50;
	blocktype = 0;
	AllMap::init();
	potalposX = -500;
	potalposY = -500;
	bg[0] = IMAGEMANAGER->findImage("∏º¿∫«œ¥√");
	bg[1] = IMAGEMANAGER->findImage("πË∞Ê4");
	MonsterMG->set_Boss({ 1400,400 });
	alphavalue = 254;
	isdark = false;
	return S_OK;
}

void BossMap::release()
{
}

void BossMap::update()
{
	AllMap::update();
	MonsterAndMapCollion(1);
	PlayerAndMapCollion(1, 0, 0);

	if(!isdark)
	alphavalue -= 3;
	if (isdark)
	{
		bg[0] = IMAGEMANAGER->findImage("∞À¿∫«œ¥√");
		alphavalue += 3;
	}

	if (alphavalue <= 0)
		isdark = true;

	if (alphavalue >= 255)
		alphavalue = 255;

}

void BossMap::render()
{
	
	bg[0]->alphaRender(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), alphavalue);
		bg[1]->loopRender(CAMERAMANAGER->getWorldDC(), &RectMake(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY());
	
	AllMap::render();
}
