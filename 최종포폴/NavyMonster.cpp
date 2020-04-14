#include "stdafx.h"
#include "NavyMonster.h"


NavyMonster::NavyMonster()
{
}


NavyMonster::~NavyMonster()
{
}

HRESULT NavyMonster::init(POINT pos)
{

	monsterindex = 6;
	monsterinfo.pos = pos;
	monsterinfo.img = IMAGEMANAGER->findImage("�ر������̵�");
	monsterinfo.currentFrameX = 0;
	monsterinfo.currentFrameY = 0;
	monsterinfo.rc = RectMake(monsterinfo.pos.x + 10, monsterinfo.pos.y + 10, 60, 100);
	RL = false;
	playercheak = false;
	monsterinfo.MaxframeX = 7;
	range = 500;
	bulletfire = false;
	
	EFFECTMANAGER->addEffect("�ر�����", "./resours/effect/�ر�����Ʈ.bmp", 1560, 73, 260, 73, 1.f, 0.1f, 5);

	//����� ����
	IMAGEMANAGER->addImage("monster6frontBar", "hpBarTop.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("monster6backBar", "hpBarBottom.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	monsterhpBar = new progressBar;
	monsterhpBar->init("monster6", monsterinfo.rc.left, monsterinfo.rc.top - 20, monsterinfo.rc.right - monsterinfo.rc.left, 10);
	monstercurrentHP = monstermaxHP = 100;

	return S_OK;
}

void NavyMonster::release()
{
}

void NavyMonster::update()
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
		if (count % 20 == 0)
		{
			monsterinfo.currentFrameX++;
			count = 0;
		}
		if (monsterinfo.currentFrameX > monsterinfo.MaxframeX)
		{

			monsterinfo.currentFrameX = 0;

		}



		monsterinfo.rc = RectMake(monsterinfo.pos.x + 10, monsterinfo.pos.y + 10, 60, 100);
		EFFECTMANAGER->update();
	}
}

void NavyMonster::render()
{
	RECT a = CAMERAMANAGER->getCamera_Rect();
	RECT temp;
	if (IntersectRect(&temp, &a, &monsterinfo.rc))
	{
		monsterinfo.img->frameRender(CAMERAMANAGER->getWorldDC(), monsterinfo.pos.x, monsterinfo.pos.y, monsterinfo.currentFrameX, monsterinfo.currentFrameY);

		Monster::render();
	}
	
}

void NavyMonster::Move()
{


	if (isHit)
	{
		monsterinfo.img = IMAGEMANAGER->findImage("�ر������ǰ�");

		hitcount++;
		if (PlayerPosX > monsterinfo.pos.x)
		{
			if (MapRect.left <= monsterinfo.rc.left)
			{
				monsterinfo.pos.x -= 2;
			}
				monsterinfo.MaxframeX = 2;
			
			monsterinfo.currentFrameY = 0;
		}
		if (PlayerPosX < monsterinfo.pos.x)
		{
			if (MapRect.right >= monsterinfo.rc.right)
			{
				monsterinfo.pos.x += 2;
			}
				monsterinfo.MaxframeX = 2;
			
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


		if (playercheak)
		{
			

			//�÷��̾ ���� �Ÿ��ȿ� ��������
			if (getDistance(monsterinfo.pos.x, monsterinfo.pos.y, PlayerPosX - 68, monsterinfo.pos.y) < range) //  �Ÿ� ���ؼ� �Ѿư��� ����
			{
				// �÷��̾ ���ʿ� ������ �������� ����
				if (PlayerPosX < monsterinfo.pos.x)
				{
					monsterinfo.img = IMAGEMANAGER->findImage("�ر��������");
					monsterinfo.MaxframeX = 5;
					monsterinfo.currentFrameY = 1;
					// ���� ����϶� ���� ��Ʈ ������ش�
					if (monsterinfo.currentFrameX == 2 && count == 15)
					{
						EFFECTMANAGER->play("�ر�����", PlayerPosX, monsterinfo.pos.y + 80);
						monsterinfo.atkRC = RectMakeCenter(PlayerPosX, monsterinfo.pos.y + 80, 200, 100);
					}
					else
					{
						monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x, monsterinfo.pos.y, 0, 0);
					}
				}
				// �÷��̾ �����ʿ� ������ ���������� ����
				else if (PlayerPosX > monsterinfo.pos.x)
				{
					monsterinfo.img = IMAGEMANAGER->findImage("�ر��������");
					monsterinfo.MaxframeX = 5;
					monsterinfo.currentFrameY = 0;
					// ���� ����϶� ���� ��Ʈ ������ش�
					if (monsterinfo.currentFrameX == monsterinfo.MaxframeX - 2 && count ==15)
					{
						EFFECTMANAGER->play("�ر�����", PlayerPosX, monsterinfo.pos.y + 80);
						monsterinfo.atkRC = RectMakeCenter(PlayerPosX, monsterinfo.pos.y + 80, 200, 100);
					}
					else
					{
						monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x, monsterinfo.pos.y, 0, 0);
					}
				}

			}
			else if (PlayerPosX < monsterinfo.pos.x)
			{
				monsterinfo.img = IMAGEMANAGER->findImage("�ر������̵�");
				monsterinfo.MaxframeX = 7;
				monsterinfo.pos.x -= 3;
				monsterinfo.currentFrameY = 1;
				monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x, monsterinfo.pos.y, 0, 0);
			}
			else if (PlayerPosX > monsterinfo.pos.x)
			{

				monsterinfo.img = IMAGEMANAGER->findImage("�ر������̵�");
				monsterinfo.MaxframeX = 7;
				monsterinfo.pos.x += 3;
				monsterinfo.currentFrameY = 0;
				monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x, monsterinfo.pos.y, 0, 0);
			}


		}
		else {
			monsterinfo.img = IMAGEMANAGER->findImage("�ر������̵�");
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
