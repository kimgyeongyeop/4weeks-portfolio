#include "stdafx.h"
#include "GetAngleMonster.h"


GetAngleMonster::GetAngleMonster()
{
}


GetAngleMonster::~GetAngleMonster()
{
}

HRESULT GetAngleMonster::init(POINT pos)
{
	monsterindex = 7;
	monsterinfo.pos = pos;
	monsterinfo.img = IMAGEMANAGER->findImage("��ī��Ű���ͱ⺻");
	monsterinfo.currentFrameX = 0;
	monsterinfo.currentFrameY = 0;
	monsterinfo.rc = RectMake(monsterinfo.pos.x + 20, monsterinfo.pos.y + 5, 50, 100);
	RL = false;
	playercheak = false;
	monsterinfo.MaxframeX = 1;
	range = 500;
	bulletfire = false;
	count = 0;
	bulletdelaytime = 0;

	
	EFFECTMANAGER->addEffect("����ġ������Ʈ", "./resours/effect/��������Ʈ.bmp", 356, 109, 89, 109, 1.f, 0.05f, 5);


	//����� ����
	IMAGEMANAGER->addImage("monster7frontBar", "hpBarTop.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("monster7backBar", "hpBarBottom.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	monsterhpBar = new progressBar;
	monsterhpBar->init("monster7", monsterinfo.rc.left, monsterinfo.rc.top - 20, monsterinfo.rc.right - monsterinfo.rc.left, 10);
	monstercurrentHP = monstermaxHP = 100;

	isHit = false;
	hitcount = 0;
	monsterinfo.img = IMAGEMANAGER->findImage("��ī��Ű��������");
	return S_OK;
}

void GetAngleMonster::release()
{
}

void GetAngleMonster::update()
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
		monsterinfo.rc = RectMake(monsterinfo.pos.x + 20, monsterinfo.pos.y + 5, 50, 100);

		EFFECTMANAGER->update();
	
}

void GetAngleMonster::render()
{
	

		monsterinfo.img->frameRender(CAMERAMANAGER->getWorldDC(), monsterinfo.pos.x, monsterinfo.pos.y + imgY, monsterinfo.currentFrameX, monsterinfo.currentFrameY);

		Monster::render();
	
}

void GetAngleMonster::Move()
{

	if (isHit)
	{
		bulletfire = false;
		monsterinfo.img = IMAGEMANAGER->findImage("��ī��Ű�����ǰ�");

		hitcount++;
		if (PlayerPosX > monsterinfo.pos.x)
		{
			if (MapRect.left <= monsterinfo.rc.left)
			{
				monsterinfo.pos.x -= 2;
			}
			
			imgY = 0;
			monsterinfo.MaxframeX = 1;
			monsterinfo.currentFrameY = 0;
		}
		if (PlayerPosX < monsterinfo.pos.x)
		{
			if (MapRect.right >= monsterinfo.rc.right)
			{
				monsterinfo.pos.x += 2;
			}
			imgY = 0;
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

		//ī�޶�����ȿ� ���Ͱ� ��������
		RECT temp;

		if (playercheak)
		{
			imgY = -30;
			monsterinfo.MaxframeX = 2;
			monsterinfo.img = IMAGEMANAGER->findImage("��ī��Ű��������");

			EFFECTMANAGER->play("����ġ������Ʈ", monsterinfo.pos.x + 24, monsterinfo.pos.y);

			int randomX = RND->getFromFloatTo(AngleMonsterRect.left, AngleMonsterRect.right);
			monsterinfo.pos.y = AngleMonsterRect.top - 90;
			monsterinfo.pos.x = randomX;


			bulletfire = false;
		}

		else
		{
			imgY = -30;
			if (AngleMonsterPlayerPosX < monsterinfo.pos.x) monsterinfo.currentFrameY = 1;
			if (AngleMonsterPlayerPosX > monsterinfo.pos.x) monsterinfo.currentFrameY = 0;
			monsterinfo.MaxframeX = 1;
			monsterinfo.img = IMAGEMANAGER->findImage("��ī��Ű��������");
			bulletdelaytime++;
			if (bulletdelaytime % 100 == 0)
			{
				bulletfire = true;
				bulletdelaytime = 0;
			}
			else
			{
				bulletfire = false;
			}

		}

	}
}
