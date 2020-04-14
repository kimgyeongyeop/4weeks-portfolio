#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
{
}


selectScene::~selectScene()
{
}

HRESULT selectScene::init()
{
	_btnSceneChange = new button;
	_btnSceneChange->init("¹öÆ°", WINSIZEX / 2, WINSIZEY / 2,
		PointMake(0, 1), PointMake(0, 0), cbSceneChange);

	testImage = IMAGEMANAGER->addImage("ÃÑ¾Ë", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));
	testImage->setX(WINSIZEX / 2);
	testImage->setY(WINSIZEY / 2);

	_actionTest = new action;
	_actionTest->init();

	_actionTest->moveTo(testImage, 500, 100, 2.0f, cbAction);

	actionTest = _actionTest;
	

	return S_OK;
}

void selectScene::release()
{
}

void selectScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("½ºÅ¸¾À");

	_btnSceneChange->update();
	_actionTest->update();
}

void selectScene::render()
{
	char str[128];
	sprintf_s(str, "¼¿·ºÆ®¾À");
	TextOut(getMemDC(), WINSIZEX / 2 - 200, WINSIZEY / 2, str, strlen(str));

	_btnSceneChange->render();
	testImage->render(getMemDC(), testImage->getX(), testImage->getY());
}

void selectScene::cbSceneChange()
{
	SCENEMANAGER->changeScene("½ºÅ¸¾À");
}

void selectScene::cbAction()
{
	actionTest->moveTo(testImage, RND->getFromIntTo(100, 500), RND->getFromIntTo(100, 500), RND->getFromFloatTo(1.0f, 5.0f), cbAction);
}
