#include "stdafx.h"
#include "PirateMonster.h"


PirateMonster::PirateMonster()
{
}


PirateMonster::~PirateMonster()
{
}

HRESULT PirateMonster::init(POINT pos)
{
	monsterindex = 5;
	monsterinfo.pos = pos;
	monsterinfo.img = IMAGEMANAGER->findImage("해적총알공격");
	monsterinfo.currentFrameX = 0;
	monsterinfo.currentFrameY = 0;
	monsterinfo.rc = RectMake(monsterinfo.pos.x+60, monsterinfo.pos.y+60,
		150, monsterinfo.img->getFrameHeight());
	RL = false;
	playercheak = false;
	monsterinfo.MaxframeX = 4;
	range = 200;
	bulletangle = 0;
	limitcount = 50;
	bulletfire = false;

	EFFECTMANAGER->addEffect("해적이펙", "./resours/effect/해적이펙트2.bmp", 1200, 168, 400, 168, 1.f, 0.1f, 5);


	//목숨바 설정
	IMAGEMANAGER->addImage("monster5frontBar", "hpBarTop.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("monster5backBar", "hpBarBottom.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	monsterhpBar = new progressBar;
	monsterhpBar->init("monster5", monsterinfo.rc.left, monsterinfo.rc.top - 20, monsterinfo.rc.right - monsterinfo.rc.left, 10);
	monstercurrentHP = monstermaxHP = 100;
	return S_OK;
}

void PirateMonster::release()
{
}

void PirateMonster::update()
{
	
		monsterhpBar->update();
		monsterhpBar->setX(monsterinfo.rc.left);
		monsterhpBar->setY(monsterinfo.rc.top - 20);

		monsterhpBar->setGauge(monstercurrentHP, monstermaxHP);

		Move();

		count++;
		if (count % limitcount == 0)
		{
			monsterinfo.currentFrameX++;
			count = 0;
		}
		if (monsterinfo.currentFrameX > monsterinfo.MaxframeX) {

			monsterinfo.currentFrameX = 0;

		}

	
}

void PirateMonster::render()
{
	
		//EFFECTMANAGER->render();
		monsterinfo.img->frameRender(CAMERAMANAGER->getWorldDC(), monsterinfo.pos.x, monsterinfo.pos.y, monsterinfo.currentFrameX, monsterinfo.currentFrameY);

		Monster::render();
	
}


void PirateMonster::Move()
{

	if (playercheak)
	{


		//플레이어가 공격 거리안에 들어왔을때
		if (getDistance(monsterinfo.pos.x + 50 , monsterinfo.pos.y, PlayerPosX , monsterinfo.pos.y) < range) //  거리 비교해서 쫓아가게 ㄱㄱ
		{
			bulletfire = false;
			limitcount = 30;
			monsterinfo.img = IMAGEMANAGER->findImage("해적근접공격");

			monsterinfo.MaxframeX = 7;
			if (monsterinfo.currentFrameX == monsterinfo.MaxframeX-2)
			{
			
		       CAMERAMANAGER->Camera_WorldDC_Shake();
				
				EFFECTMANAGER->play("해적이펙", monsterinfo.pos.x + 120, monsterinfo.pos.y+170);
			}
			if (monsterinfo.currentFrameX == monsterinfo.MaxframeX - 2 && count == 20)
			{
				monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x + 120, monsterinfo.pos.y + 170, 500, 250);
			}
			else
			{
				monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x + 120, monsterinfo.pos.y + 170, 0, 0);
			}
			
		}
		else
		{
			monsterinfo.MaxframeX = 4;
		     if (monsterinfo.currentFrameX == monsterinfo.MaxframeX)
			{
				if (count %limitcount == 0)
				{
					bulletfire = true;
				}
				else bulletfire = false;
			}
			limitcount = 20;
			monsterinfo.img = IMAGEMANAGER->findImage("해적총알공격");
			
		}
	}
	else
	{
		monsterinfo.MaxframeX = 4;
		if (monsterinfo.currentFrameX == monsterinfo.MaxframeX)
		{
			if (count % limitcount == 0)
			{
				bulletfire = true;
			}
			else bulletfire = false;
			
		}
		
		limitcount = 20;
		monsterinfo.img = IMAGEMANAGER->findImage("해적총알공격");
		
	}
	
}
