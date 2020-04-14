#include "stdafx.h"
#include "PoisonMonster.h"


PoisonMonster::PoisonMonster()
{
}


PoisonMonster::~PoisonMonster()
{
}

HRESULT PoisonMonster::init(POINT pos)
{
	monsterindex = 4;
	monsterinfo.pos = pos;
	monsterinfo.img = IMAGEMANAGER->findImage("µ¶²É");
	monsterinfo.currentFrameX = 0;
	monsterinfo.currentFrameY = 0;
	monsterinfo.rc = RectMake(monsterinfo.pos.x, monsterinfo.pos.y, 50, 100);
	
	//playercheak = false;
	monsterinfo.MaxframeX = 2;
	range = 500;
	bulletfire = false;
	
	EFFECTMANAGER->addEffect("µ¶»Õ´ÂÀÌÆåÆ®", "./resours/effect/µ¶ÀÌÆåÆ®1.bmp", 810, 112, 116, 112, 1.f, 0.1f, 5);

	//¸ñ¼û¹Ù ¼³Á¤
	IMAGEMANAGER->addImage("monster4frontBar", "hpBarTop.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("monster4backBar", "hpBarBottom.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	monsterhpBar = new progressBar;
	monsterhpBar->init("monster4", monsterinfo.rc.left, monsterinfo.rc.top - 20, monsterinfo.rc.right - monsterinfo.rc.left, 10);
	monstercurrentHP = monstermaxHP = 100;
	return S_OK;
}

void PoisonMonster::release()
{
}

void PoisonMonster::update()
{
	RECT a = CAMERAMANAGER->getCamera_Rect();
	RECT temp;
	if (IntersectRect(&temp, &a, &monsterinfo.rc))
	{
		monsterhpBar->update();
		monsterhpBar->setX(monsterinfo.rc.left);
		monsterhpBar->setY(monsterinfo.rc.top - 20);

		monsterhpBar->setGauge(monstercurrentHP, monstermaxHP);


		count++;
		if (count % 50 == 0)
		{
			monsterinfo.currentFrameX++;
			count = 0;
		}
		if (monsterinfo.currentFrameX > monsterinfo.MaxframeX) {

			monsterinfo.currentFrameX = 0;

		}

		if (monsterinfo.currentFrameX == 2 && count==30)
		{
			monsterinfo.atkRC = RectMake(monsterinfo.pos.x, monsterinfo.pos.y, 100, 100);
			EFFECTMANAGER->play("µ¶»Õ´ÂÀÌÆåÆ®", monsterinfo.pos.x + 24, monsterinfo.pos.y);
		}
		else
		{
			monsterinfo.atkRC = RectMake(monsterinfo.pos.x, monsterinfo.pos.y, 0, 0);
		}



	}
}

void PoisonMonster::render()
{
	RECT a = CAMERAMANAGER->getCamera_Rect();
	RECT temp;
	if (IntersectRect(&temp, &a, &monsterinfo.rc))
	{
		monsterinfo.img->frameRender(CAMERAMANAGER->getWorldDC(), monsterinfo.pos.x, monsterinfo.pos.y, monsterinfo.currentFrameX, monsterinfo.currentFrameY);


		Monster::render();
	}
}

void PoisonMonster::Move()
{

}
