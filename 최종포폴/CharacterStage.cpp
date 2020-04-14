#include "stdafx.h"
#include "CharacterStage.h"


CharacterStage::CharacterStage()
{
}


CharacterStage::~CharacterStage()
{
}

HRESULT CharacterStage::init()
{
	SOUNDMANAGER->play("배경음악", 6);
	DATA->playerInfo.currentmapindex = 8;
	_MAP = IMAGEMANAGER->findImage("캐릭터스테이지");
	CAMERAMANAGER->set_CameraWorldSize(2200, 1200);


	

	maprc[0].rc = RectMake(0, 874, 788, 100);
	maprc[1].rc = RectMake(792, 605, 791, 100);
	maprc[2].rc = RectMake(1587, 876, 613, 100);
	store = IMAGEMANAGER->findImage("상점");

	

	rightmaprc[0].rc = RectMake(1565, 609, 20, 300);
	leftmaprc[0].rc = RectMake(790, 609, 20, 300);
	DATA->playerInfo.locationX = 50;
	DATA->playerInfo.locationY = 200;
	AllMap::init();
	bg[0] = IMAGEMANAGER->findImage("맑은하늘");
	bg[1] = IMAGEMANAGER->findImage("배경5");
	potalposX = 1900;
	potalposY = 602;

	blocktype = 0;
	storerc = RectMake(1063, 450, store->getWidth(), store->getHeight());
	Once = false;
	return S_OK;
}

void CharacterStage::release()
{
}

void CharacterStage::update()
{
	AllMap::update();
	MonsterAndMapCollion(3);
	PlayerAndMapCollion(3, 1, 1);
	//MakePotalCollison("상점스테이지");
	MakePotalCollison();
	RECT temp;
	if (IntersectRect(&temp,&player->GetPlayerRC(),&storerc))
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			if (!Once)
			{

				int rand = RND->getFromIntTo(1, 4);
				if(rand==1)
				ItemMG->set_NarutoBook((storerc.right + storerc.left) / 2-10, (storerc.top + storerc.bottom) / 2);
				else if (rand == 2)
				ItemMG->set_LuffyBook((storerc.right + storerc.left) / 2- 10, (storerc.top + storerc.bottom) / 2);
				else if (rand == 3)
				ItemMG->set_SonoGongBook((storerc.right + storerc.left) / 2- 10, (storerc.top + storerc.bottom) / 2);
				Once = true;
			}
		}
	}
}

void CharacterStage::render()
{

	for (int i = 0; i < 2; ++i)
	{

		bg[i]->loopRender(CAMERAMANAGER->getWorldDC(), &RectMake(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY), CAMERAMANAGER->get_CameraX()*i*0.5f, CAMERAMANAGER->get_CameraY());
	}
	store->render(CAMERAMANAGER->getWorldDC(), 1063, 450);
	//Rectangle(CAMERAMANAGER->getWorldDC(), storerc);
	
	AllMap::render();
	
}
