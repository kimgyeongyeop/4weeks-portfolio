#include "stdafx.h"
#include "FlowerMonster.h"


FlowerMonster::FlowerMonster()
{
}


FlowerMonster::~FlowerMonster()
{
}

HRESULT FlowerMonster::init(POINT pos)
{
	monsterindex = 2;
	monsterinfo.pos = pos;
	monsterinfo.img = IMAGEMANAGER->findImage("몬스터꽃");
	monsterinfo.currentFrameX = 0;
	monsterinfo.currentFrameY = 0;
	monsterinfo.rc = RectMake(monsterinfo.pos.x+10, monsterinfo.pos.y+10, 
		50, 100);
	RL = false;
	playercheak = false;
	monsterinfo.MaxframeX = 4;
	range = 500;
	bulletangle = 0;
	bulletfire = false;


	IMAGEMANAGER->addImage("monster2frontBar", "hpBarTop.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("monster2backBar", "hpBarBottom.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	monsterhpBar = new progressBar;
	monsterhpBar->init("monster2", monsterinfo.rc.left, monsterinfo.rc.top - 20, monsterinfo.rc.right - monsterinfo.rc.left, 10);
	monstercurrentHP = monstermaxHP = 100;


	return S_OK;
}

void FlowerMonster::release()
{
}

void FlowerMonster::update()
{
	RECT a = CAMERAMANAGER->getCamera_Rect();
	RECT temp;
	if (IntersectRect(&temp, &a, &monsterinfo.rc))
	{
		monsterhpBar->update();
		monsterhpBar->setX(monsterinfo.rc.left);
		monsterhpBar->setY(monsterinfo.rc.top - 20);

		monsterhpBar->setGauge(monstercurrentHP, monstermaxHP);


		Move();
		//MonsterBulletFire();

		count++;
		if (count % 20 == 0)
		{
			monsterinfo.currentFrameX++;
			count = 0;
		}
		if (monsterinfo.currentFrameX > monsterinfo.MaxframeX) {

			monsterinfo.currentFrameX = 0;

		}




	}

	
}

void FlowerMonster::render()
{
	RECT a = CAMERAMANAGER->getCamera_Rect();
	RECT temp;
	if (IntersectRect(&temp, &a, &monsterinfo.rc))
	{
		monsterinfo.img->frameRender(CAMERAMANAGER->getWorldDC(), monsterinfo.pos.x, monsterinfo.pos.y, monsterinfo.currentFrameX, monsterinfo.currentFrameY);
		Monster::render();
	}
}

void FlowerMonster::Move()
{
	//플레이어가 몬스터의 추적범위에 들어왔을때!!!
	if (playercheak)
	{


		//플레이어가 공격 거리안에 들어왔을때
		if (getDistance(monsterinfo.pos.x, monsterinfo.pos.y, PlayerPosX - 68, monsterinfo.pos.y) < range) //  거리 비교해서 쫓아가게 ㄱㄱ
		{
			// 플레이어가 왼쪽에 있으면 왼쪽으로 공격
			if (PlayerPosX < monsterinfo.pos.x)
			{
				bulletangle = DO * 180;

				monsterinfo.currentFrameY = 1;
				// 공격 모션일때 총알쏜다
				if (monsterinfo.currentFrameX == 0)
				{
					if (count % 20 == 0)bulletfire = true;
					else bulletfire = false;
				}
				else bulletfire = false;

			}
			// 플레이어가 오른쪽에 있으면 오른쪽으로 공격
			else if (PlayerPosX > monsterinfo.pos.x)
			{
				bulletangle = DO * 0;
				monsterinfo.currentFrameY = 0;
				// 공격 모션일때 총알쏜다
				if (monsterinfo.currentFrameX == monsterinfo.MaxframeX)
				{
					if (count % 20 == 0)bulletfire = true;
					else bulletfire = false;
				}
				else bulletfire = false;
			}

		}

	}
	else
	{
		bulletfire = false;
	}
}




