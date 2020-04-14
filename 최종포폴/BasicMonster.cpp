#include "stdafx.h"
#include "BasicMonster.h"


BasicMonster::BasicMonster()
{
}


BasicMonster::~BasicMonster()
{
}

HRESULT BasicMonster::init(POINT pos)
{
	monsterindex = 1;
	monsterinfo.pos = pos;
	monsterinfo.img = IMAGEMANAGER->findImage("몬스터1이동");
	monsterinfo.currentFrameX = 0;
	monsterinfo.currentFrameY = 0;
	monsterinfo.rc = RectMake(monsterinfo.pos.x, monsterinfo.pos.y + 5, 60, 100);
	RL = false;
	playercheak = false;
	monsterinfo.MaxframeX = 3;
	range = 110;
	bulletfire = false;
	
	//목숨바 설정
	IMAGEMANAGER->addImage("monster1frontBar", "hpBarTop.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("monster1backBar", "hpBarBottom.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	monsterhpBar = new progressBar;
	monsterhpBar->init("monster1",monsterinfo.rc.left, monsterinfo.rc.top - 20, monsterinfo.rc.right - monsterinfo.rc.left, 10);
	monstercurrentHP = monstermaxHP = 100;
	isHit = false;
	hitcount = 0;
	intervel = 0;
	return S_OK;
}

void BasicMonster::release()
{
}

void BasicMonster::update()
{
	RECT a = CAMERAMANAGER->getCamera_Rect();
	RECT temp;
	if (IntersectRect(&temp, &a, &monsterinfo.rc))
	{


	monsterhpBar->update();
	monsterhpBar->setX(monsterinfo.rc.left);
	monsterhpBar->setY(monsterinfo.rc.top  - 20);
	
	monsterhpBar->setGauge(monstercurrentHP, monstermaxHP);

	

	Move();
	count++;
	if (count % 10 == 0)
	{
		monsterinfo.currentFrameX++;
		count = 0;
	}
	if (monsterinfo.currentFrameX> monsterinfo.img->getMaxFrameX()) {

		monsterinfo.currentFrameX=0;
		
	}
	

	//monsterinfo.pos.y + 5
	monsterinfo.rc = RectMake(monsterinfo.pos.x, monsterinfo.pos.y+5, 60, 100);
	}
}

void BasicMonster::render()
{
	RECT a = CAMERAMANAGER->getCamera_Rect();
	RECT temp;
	if (IntersectRect(&temp, &a, &monsterinfo.rc))
	{
		monsterinfo.img->frameRender(CAMERAMANAGER->getWorldDC(), monsterinfo.pos.x, monsterinfo.pos.y + 10, monsterinfo.currentFrameX, monsterinfo.currentFrameY);

		Monster::render();

	}
}

void BasicMonster::Move()
{
	//플레이어가 몬스터의 추적범위에 들어왔을때!!!
	
	if (isHit)
	{
		monsterinfo.img = IMAGEMANAGER->findImage("몬스터1피격");
		
		hitcount++;
		if (PlayerPosX > monsterinfo.pos.x)
		{
			if (MapRect.left <= monsterinfo.rc.left)
			{
				monsterinfo.pos.x -= 2;
			}
			monsterinfo.MaxframeX = 0;
			monsterinfo.currentFrameY = 0;
		}
		if (PlayerPosX < monsterinfo.pos.x)
		{

			if (MapRect.right >= monsterinfo.rc.right)
			{
				monsterinfo.pos.x += 2;
			}
			monsterinfo.MaxframeX = 0;
			monsterinfo.currentFrameY = 1;
		}

	


	


		if (hitcount % 30 == 0)
		{
			hitcount = 0;
			isHit = false;
		}
	}

	if(!isHit)
	{ 
	if (playercheak)
	{
		
		
		//플레이어가 공격 거리안에 들어왔을때
		if (getDistance(monsterinfo.pos.x, monsterinfo.pos.y, PlayerPosX - 68, monsterinfo.pos.y) < range) //  거리 비교해서 쫓아가게 ㄱㄱ
		{

			if (getDistance(monsterinfo.pos.x, monsterinfo.pos.y, PlayerPosX - 68, monsterinfo.pos.y) < range || intervel<50) //  거리 비교해서 쫓아가게 ㄱㄱ
			{
				monsterinfo.img = IMAGEMANAGER->findImage("몬스터1기본");
				intervel++;
				//cout << intervel << endl;
			}
			// 플레이어가 왼쪽에 있으면 왼쪽으로 공격
			
				//intervel++;
				//monsterinfo.img = IMAGEMANAGER->findImage("몬스터1기본");
			

			//monsterinfo.img = IMAGEMANAGER->findImage("몬스터1공격");
			
				if (PlayerPosX < monsterinfo.pos.x && intervel>=50)
				{
					
					monsterinfo.img = IMAGEMANAGER->findImage("몬스터1공격");
					
					monsterinfo.MaxframeX = 2;
					monsterinfo.currentFrameY = 1;
					// 공격 모션일때 공격 렉트 만들어준다
					if (monsterinfo.currentFrameX == 0)
					{
						if (count == 5)
						{
							monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x - 30, monsterinfo.pos.y + 50, 80, 100);
							
						}
						else
						{
							monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x, monsterinfo.pos.y, 0, 0);
						}
					}
					else {
						monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x, monsterinfo.pos.y, 0, 0);
					}
					if (intervel > 100)
						intervel = 0;
				}
				// 플레이어가 오른쪽에 있으면 오른쪽으로 공격
				else if (PlayerPosX > monsterinfo.pos.x&& intervel >= 50)
				{
					monsterinfo.img = IMAGEMANAGER->findImage("몬스터1공격");
					
					monsterinfo.MaxframeX = 2;
					monsterinfo.currentFrameY = 0;
					// 공격 모션일때 공격 렉트 만들어준다
					if (monsterinfo.currentFrameX == 2)
					{
						if (count == 5)
						{
							monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x + 150, monsterinfo.pos.y + 50, 80, 100);
							//intervel = 0;
						}
						else
						{
							monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x, monsterinfo.pos.y, 0, 0);
						}
					}
					else
					{
						monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x, monsterinfo.pos.y, 0, 0);
					}
					if(intervel>100)
					intervel = 0;
				}

			}

		
		else if (PlayerPosX < monsterinfo.pos.x)
		{
			monsterinfo.img = IMAGEMANAGER->findImage("몬스터1이동");
			monsterinfo.MaxframeX = 3;
			monsterinfo.pos.x -= 5;
			monsterinfo.currentFrameY = 1;
			monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x, monsterinfo.pos.y, 0, 0);
		}
		else if (PlayerPosX > monsterinfo.pos.x)
		{
			monsterinfo.pos.x += 5;
			monsterinfo.img = IMAGEMANAGER->findImage("몬스터1이동");
			monsterinfo.MaxframeX = 3;
			monsterinfo.currentFrameY = 0;
			monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x, monsterinfo.pos.y, 0, 0);
		}
	
		
	}
	else {
		monsterinfo.img = IMAGEMANAGER->findImage("몬스터1이동");
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


