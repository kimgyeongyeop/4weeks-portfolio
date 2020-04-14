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
	monsterinfo.img = IMAGEMANAGER->findImage("���ݷθ����̵�");
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
	
	//IMAGEMANAGER->addImage("����", "./resours/effect/explosion.bmp", 832, 62, true, RGB(255, 0, 255));
	
	EFFECTMANAGER->addEffect("�����ʰ������Ʈ", "./resours/effect/����������ü���.bmp", 143, 120, 143, 40, 1.f, 0.3f, 50);
	EFFECTMANAGER->addEffect("���ʰ������Ʈ", "./resours/effect/��������ü���.bmp", 143, 120, 143, 40, 1.f, 0.3f, 50);
	//_effect->init(IMAGEMANAGER->findImage("����"), 32, 62, 1.f, 1.f);
	//EFFECTMANAGER->addEffect("explosion", "./resours/effect/explosion.bmp", 832, 62, 32, 62, 1.f, 1.f, 50);

	//����� ����
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
		monsterinfo.img = IMAGEMANAGER->findImage("���ݷθ����ǰ�");

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



		//�÷��̾ ������ ���������� ��������!!!
		if (playercheak)
		{


			//�÷��̾ ���� �Ÿ��ȿ� ��������
			if (getDistance(monsterinfo.pos.x, monsterinfo.pos.y, PlayerPosX - 68, monsterinfo.pos.y) < range) //  �Ÿ� ���ؼ� �Ѿư��� ����
			{
				// �÷��̾ ���ʿ� ������ �������� ����
				if (PlayerPosX < monsterinfo.pos.x)
				{
					bulletangle = DO * 180;
					monsterinfo.img = IMAGEMANAGER->findImage("���ݷθ��Ͱ���");

					monsterinfo.currentFrameY = 1;


					if (monsterinfo.currentFrameX == 1 || monsterinfo.currentFrameX==5)
					{

						if (count == 5 )
						{
							//EFFECTMANAGER->play("���ʰ������Ʈ", monsterinfo.pos.x - 80, monsterinfo.pos.y + 40);
							bulletfire = true;
						}
						else bulletfire = false;


					}
					else
					{
						bulletfire = false;
					}
				}
				// �÷��̾ �����ʿ� ������ ���������� ����
				else if (PlayerPosX > monsterinfo.pos.x)
				{
					monsterinfo.img = IMAGEMANAGER->findImage("���ݷθ��Ͱ���");
					bulletangle = DO * 0;
					monsterinfo.currentFrameY = 0;




					// ���� ����϶� ���� ��Ʈ ������ش�
					if (monsterinfo.currentFrameX == 5 || monsterinfo.currentFrameX ==1)
					{

						if (count ==5)
						{
							//EFFECTMANAGER->play("�����ʰ������Ʈ", monsterinfo.pos.x + 150, monsterinfo.pos.y + 40);
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
				monsterinfo.img = IMAGEMANAGER->findImage("���ݷθ����̵�");

				monsterinfo.pos.x -= 3;
				monsterinfo.currentFrameY = 1;
				
			}
			else if (PlayerPosX > monsterinfo.pos.x)
			{
				bulletfire = false;
				monsterinfo.pos.x += 3;
				monsterinfo.img = IMAGEMANAGER->findImage("���ݷθ����̵�");

				monsterinfo.currentFrameY = 0;
				
			}


		}
		else {
			bulletfire = false;
			monsterinfo.img = IMAGEMANAGER->findImage("���ݷθ����̵�");
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

