#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}


HRESULT playGround::init()
{
	gameNode::init(true);

	GM = new GameSceneManager;
	GM->init();
	

	return S_OK;
}


void playGround::release()
{
	gameNode::release();
	GM->release();

}


void playGround::update()
{
	gameNode::update();

	GM->update();

}



void playGround::render()
{
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY, BLACKNESS);

	GM->render();

	//===========================================================
	_backBuffer->render(getHDC(), 0, 0);
}
