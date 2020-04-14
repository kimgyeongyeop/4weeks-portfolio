#include "stdafx.h"
#include "InStage.h"


InStage::InStage()
{
}


InStage::~InStage()
{
}

HRESULT InStage::init()
{
	SOUNDMANAGER->play("배경음악", 6);
	DATA->playerInfo.currentmapindex = 1;
	CAMERAMANAGER->set_CameraWorldSize(2160, 1800);

	_MAP = new image;
	_MAP = IMAGEMANAGER->findImage("인스테이지맵");
	

	

	maprc[0].rc = RectMake(124, 321, 360, 20);
	maprc[1].rc = RectMake(1072, 324, 360, 20);
	maprc[2].rc = RectMake(610, 630, 360, 20);
	maprc[3].rc = RectMake(128, 905, 360, 20);
	maprc[4].rc = RectMake(1085, 905, 360, 20);
	maprc[5].rc = RectMake(609, 1132, 360, 20);
	maprc[6].rc = RectMake(125, 1386, 360, 20);
	maprc[7].rc = RectMake(1076, 1358, 360, 20); //1358
	maprc[8].rc = RectMake(0, 1658, 2158, 100);
	//init하기전에 위치설정
	DATA->playerInfo.locationX = 770;
	DATA->playerInfo.locationY = 1530;
	AllMap::init();
	
	potalposX = 100;
	potalposY = 28;
	blocktype = 8;

	
	//potal= RectMakeCenter(200, 200, 3000, 3000);
	//MakePotalCollison(string a, int centerX, int centerY);
	return S_OK;
}

void InStage::release()
{
	
}

void InStage::update()
{
	AllMap::update();
	
	PlayerAndMapCollion(9, 0, 0);
	MakePotalCollison("캐릭터스테이지");
}

void InStage::render()
{
	


	for (int i = 0; i < 3; ++i)
	{
		
		bg[i]->loopRender(CAMERAMANAGER->getWorldDC(), &RectMake(CAMERAMANAGER->get_CameraX(), 
			CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY), CAMERAMANAGER->get_CameraX()*i*0.5f, CAMERAMANAGER->get_CameraY() );
	}
	//bg[i]->loopRender(CAMERAMANAGER->getWorldDC(), &RectMake(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY());
	
	/*bg[0]->loopRender(CAMERAMANAGER->getWorldDC(), &RectMake(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY),  loopX1, CAMERAMANAGER->get_CameraY());
	bg[1]->loopRender(CAMERAMANAGER->getWorldDC(), &RectMake(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY),  loopX2, CAMERAMANAGER->get_CameraY());
	bg[2]->loopRender(CAMERAMANAGER->getWorldDC(), &RectMake(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY),  loopX3, CAMERAMANAGER->get_CameraY());*/
	AllMap::render();

	
	//cout << DATA->playerInfo.playerHP << endl;
	//cout << potal.right << "," << potal.bottom << endl;
}




