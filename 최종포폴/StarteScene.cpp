#include "stdafx.h"
#include "StarteScene.h"


StarteScene::StarteScene()
{
}


StarteScene::~StarteScene()
{
}

HRESULT StarteScene::init()
{
	//CAMERAMANAGER->set_CameraWorldSize(WINSIZEX, WINSIZEY);
		
	_background = IMAGEMANAGER->addFrameImage("����ȭ��", "���۾�.bmp", 12000, 900, 8, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���۹�ư", "���۹�ư.bmp",0, 0, 350, 202, 1, 2,true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ɼǹ�ư", "�ɼǹ�ư.bmp", 0, 0, 350, 202, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������ư", "�������ư.bmp", 0, 0, 350, 202, 1, 2, true, RGB(255, 0, 255));
	

	startbutton = new button;
	startbutton->init("���۹�ư", 68, 97, PointMake(0, 1), PointMake(0, 0), ChangeStartScene);
	
	exitbotton = new button;
	exitbotton->init("�������ư", 68, 561,PointMake(0, 1), PointMake(0, 0), Exit);

	framecount = 0;
	currentFrameX = currentFrameY = 0;
	return S_OK;
}

void StarteScene::release()
{
	
}

void StarteScene::update()
{
	framecount++;
	if (currentFrameX > 7 )
	{
		currentFrameX=0;
	}
	if (framecount % 5 == 0)
	{
		currentFrameX++;
	}


	startbutton->update();
	exitbotton->update();
}

void StarteScene::render()
{
	_background->frameRender(getMemDC(), 0, 0, currentFrameX, currentFrameY);
	startbutton->render();
	exitbotton->render();

}

void StarteScene::ChangeStartScene()
{
	SCENEMANAGER->changeScene("�ε���");
}

void StarteScene::Exit()
{
	exit(0);
}
