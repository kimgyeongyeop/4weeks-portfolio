#include "stdafx.h"
#include "StoreMater.h"


StoreMater::StoreMater()
{
}


StoreMater::~StoreMater()
{
}

HRESULT StoreMater::init(POINT pos)
{
	monsterindex = 8;
	monsterinfo.pos = pos;
	monsterinfo.img = IMAGEMANAGER->findImage("상점주인");
	monsterinfo.currentFrameX = 0;
	monsterinfo.currentFrameY = 0;
	monsterinfo.rc = RectMake(monsterinfo.pos.x, monsterinfo.pos.y, monsterinfo.img->getFrameWidth(), monsterinfo.img->getFrameHeight());
	//playercheak = false;
	
	
	bulletfire = false;

	isstoremonster = true;

	//목숨바 설정
	IMAGEMANAGER->addImage("monster8frontBar", "hpBarTop.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("monster8backBar", "hpBarBottom.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	monsterhpBar = new progressBar;
	monsterhpBar->init("monster8", monsterinfo.rc.left, monsterinfo.rc.top - 20, monsterinfo.rc.right - monsterinfo.rc.left, 10);
	monstercurrentHP = monstermaxHP = 1000;
	return S_OK;
}

void StoreMater::release()
{
}

void StoreMater::update()
{
	monsterhpBar->update();
	monsterhpBar->setX(monsterinfo.rc.left);
	monsterhpBar->setY(monsterinfo.rc.top - 20);

	monsterhpBar->setGauge(monstercurrentHP, monstermaxHP);

	Move();

	count++;
	if (count % 20 == 0)
	{
		monsterinfo.currentFrameX++;
		count = 0;
	}
	if (monsterinfo.currentFrameX >= monsterinfo.img->getMaxFrameX())
	{
		monsterinfo.currentFrameX = 0;
	}
}

void StoreMater::render()
{
	RECT a = CAMERAMANAGER->getCamera_Rect();
	RECT temp;
	if (IntersectRect(&temp, &a, &monsterinfo.rc))
	{
		monsterinfo.img->frameRender(CAMERAMANAGER->getWorldDC(), monsterinfo.pos.x, monsterinfo.pos.y, monsterinfo.currentFrameX, monsterinfo.currentFrameY);


		Monster::render();
	}
}

void StoreMater::Move()
{
}
