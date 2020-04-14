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
	monsterinfo.img = IMAGEMANAGER->findImage("����1�̵�");
	monsterinfo.currentFrameX = 0;
	monsterinfo.currentFrameY = 0;
	monsterinfo.rc = RectMake(monsterinfo.pos.x, monsterinfo.pos.y + 5, 60, 100);
	RL = false;
	playercheak = false;
	monsterinfo.MaxframeX = 3;
	range = 110;
	bulletfire = false;
	
	//����� ����
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
	//�÷��̾ ������ ���������� ��������!!!
	
	if (isHit)
	{
		monsterinfo.img = IMAGEMANAGER->findImage("����1�ǰ�");
		
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
		
		
		//�÷��̾ ���� �Ÿ��ȿ� ��������
		if (getDistance(monsterinfo.pos.x, monsterinfo.pos.y, PlayerPosX - 68, monsterinfo.pos.y) < range) //  �Ÿ� ���ؼ� �Ѿư��� ����
		{

			if (getDistance(monsterinfo.pos.x, monsterinfo.pos.y, PlayerPosX - 68, monsterinfo.pos.y) < range || intervel<50) //  �Ÿ� ���ؼ� �Ѿư��� ����
			{
				monsterinfo.img = IMAGEMANAGER->findImage("����1�⺻");
				intervel++;
				//cout << intervel << endl;
			}
			// �÷��̾ ���ʿ� ������ �������� ����
			
				//intervel++;
				//monsterinfo.img = IMAGEMANAGER->findImage("����1�⺻");
			

			//monsterinfo.img = IMAGEMANAGER->findImage("����1����");
			
				if (PlayerPosX < monsterinfo.pos.x && intervel>=50)
				{
					
					monsterinfo.img = IMAGEMANAGER->findImage("����1����");
					
					monsterinfo.MaxframeX = 2;
					monsterinfo.currentFrameY = 1;
					// ���� ����϶� ���� ��Ʈ ������ش�
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
				// �÷��̾ �����ʿ� ������ ���������� ����
				else if (PlayerPosX > monsterinfo.pos.x&& intervel >= 50)
				{
					monsterinfo.img = IMAGEMANAGER->findImage("����1����");
					
					monsterinfo.MaxframeX = 2;
					monsterinfo.currentFrameY = 0;
					// ���� ����϶� ���� ��Ʈ ������ش�
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
			monsterinfo.img = IMAGEMANAGER->findImage("����1�̵�");
			monsterinfo.MaxframeX = 3;
			monsterinfo.pos.x -= 5;
			monsterinfo.currentFrameY = 1;
			monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x, monsterinfo.pos.y, 0, 0);
		}
		else if (PlayerPosX > monsterinfo.pos.x)
		{
			monsterinfo.pos.x += 5;
			monsterinfo.img = IMAGEMANAGER->findImage("����1�̵�");
			monsterinfo.MaxframeX = 3;
			monsterinfo.currentFrameY = 0;
			monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x, monsterinfo.pos.y, 0, 0);
		}
	
		
	}
	else {
		monsterinfo.img = IMAGEMANAGER->findImage("����1�̵�");
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


