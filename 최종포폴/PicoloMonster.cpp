#include "stdafx.h"
#include "PicoloMonster.h"


PicoloMonster::PicoloMonster()
{
}


PicoloMonster::~PicoloMonster()
{
}

HRESULT PicoloMonster::init(POINT pos)
{
	monsterindex = 3;
	monsterinfo.pos = pos;
	monsterinfo.img = IMAGEMANAGER->findImage("피콜로몬스터이동");
	monsterinfo.currentFrameX = 0;
	monsterinfo.currentFrameY = 0;
	monsterinfo.rc = RectMake(monsterinfo.pos.x + 10, monsterinfo.pos.y + 5, 50, 100);
	RL = false;
	playercheak = false;
	monsterinfo.MaxframeX = 5;
	range = 500;
	bulletfire = false;
	isHit = false;
	hitcount = 0;
	
	//IMAGEMANAGER->addImage("마형", "./resours/effect/explosion.bmp", 832, 62, true, RGB(255, 0, 255));
	
	EFFECTMANAGER->addEffect("오른쪽경로이펙트", "./resours/effect/오른쪽투사체경로.bmp", 143, 120, 143, 40, 1.f, 0.3f, 50);
	EFFECTMANAGER->addEffect("왼쪽경로이펙트", "./resours/effect/왼쪽투사체경로.bmp", 143, 120, 143, 40, 1.f, 0.3f, 50);
	//_effect->init(IMAGEMANAGER->findImage("마형"), 32, 62, 1.f, 1.f);
	//EFFECTMANAGER->addEffect("explosion", "./resours/effect/explosion.bmp", 832, 62, 32, 62, 1.f, 1.f, 50);

	//목숨바 설정
	IMAGEMANAGER->addImage("monster3frontBar", "hpBarTop.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("monster3backBar", "hpBarBottom.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	monsterhpBar = new progressBar;
	monsterhpBar->init("monster3", monsterinfo.rc.left, monsterinfo.rc.top - 20, (monsterinfo.rc.right - monsterinfo.rc.left)/2, 10);
	monstercurrentHP = monstermaxHP = 100;


	return S_OK;
}

void PicoloMonster::release()
{
}

void PicoloMonster::update()
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
		count++;
		if (count % 25 == 0)
		{
			monsterinfo.currentFrameX++;
			count = 0;
		}
		if (monsterinfo.currentFrameX > monsterinfo.MaxframeX) {

			monsterinfo.currentFrameX = 0;

		}
		monsterinfo.rc = RectMake(monsterinfo.pos.x + 10, monsterinfo.pos.y + 5, 50, 100);


	}
	
}

void PicoloMonster::render()
{
	RECT a = CAMERAMANAGER->getCamera_Rect();
	RECT temp;
	if (IntersectRect(&temp, &a, &monsterinfo.rc))
	{
		monsterinfo.img->frameRender(CAMERAMANAGER->getWorldDC(), monsterinfo.pos.x, monsterinfo.pos.y + 10, monsterinfo.currentFrameX, monsterinfo.currentFrameY);

		Monster::render();
	}
}

void PicoloMonster::Move()
{

	if (isHit)
	{
		bulletfire = false;
		monsterinfo.img = IMAGEMANAGER->findImage("피콜로몬스터피격");

		hitcount++;
		if (PlayerPosX > monsterinfo.pos.x)
		{
			if (MapRect.left <= monsterinfo.rc.left)
			{
				monsterinfo.pos.x -= 2;
			}
			monsterinfo.MaxframeX = 1;
			monsterinfo.currentFrameY = 0;
		}
		if (PlayerPosX < monsterinfo.pos.x)
		{

			if (MapRect.right >= monsterinfo.rc.right)
			{
				monsterinfo.pos.x += 2;
			}
			monsterinfo.MaxframeX = 1;
			monsterinfo.currentFrameY = 1;
		}



		if (hitcount % 30 == 0)
		{
			hitcount = 0;
			isHit = false;
		}

	}



	if (!isHit)
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
					monsterinfo.img = IMAGEMANAGER->findImage("피콜로몬스터공격");

					monsterinfo.currentFrameY = 1;


					if (monsterinfo.currentFrameX == 1 || monsterinfo.currentFrameX==5)
					{

						if (count == 5 )
						{
							//EFFECTMANAGER->play("왼쪽경로이펙트", monsterinfo.pos.x - 80, monsterinfo.pos.y + 40);
							bulletfire = true;
						}
						else bulletfire = false;


					}
					else
					{
						bulletfire = false;
					}
				}
				// 플레이어가 오른쪽에 있으면 오른쪽으로 공격
				else if (PlayerPosX > monsterinfo.pos.x)
				{
					monsterinfo.img = IMAGEMANAGER->findImage("피콜로몬스터공격");
					bulletangle = DO * 0;
					monsterinfo.currentFrameY = 0;




					// 공격 모션일때 공격 렉트 만들어준다
					if (monsterinfo.currentFrameX == 5 || monsterinfo.currentFrameX ==1)
					{

						if (count ==5)
						{
							//EFFECTMANAGER->play("오른쪽경로이펙트", monsterinfo.pos.x + 150, monsterinfo.pos.y + 40);
							bulletfire = true;
						}
						else bulletfire = false;
					}
					else
					{
						bulletfire = false;
					}
				}

			}
			else if (PlayerPosX < monsterinfo.pos.x)
			{
				bulletfire = false;
				monsterinfo.img = IMAGEMANAGER->findImage("피콜로몬스터이동");

				monsterinfo.pos.x -= 3;
				monsterinfo.currentFrameY = 1;
				
			}
			else if (PlayerPosX > monsterinfo.pos.x)
			{
				bulletfire = false;
				monsterinfo.pos.x += 3;
				monsterinfo.img = IMAGEMANAGER->findImage("피콜로몬스터이동");

				monsterinfo.currentFrameY = 0;
				
			}


		}
		else {
			bulletfire = false;
			monsterinfo.img = IMAGEMANAGER->findImage("피콜로몬스터이동");
			if (MapRect.left >= monsterinfo.rc.left)
			{
				RL = true;
				monsterinfo.currentFrameY = 0;
			}

			if (MapRect.right <= monsterinfo.rc.right)

			{
				RL = false;
				monsterinfo.currentFrameY = 1;
			}


			if (RL)monsterinfo.pos.x += 3;
			if (!RL)monsterinfo.pos.x -= 3;

		}


	}
}

