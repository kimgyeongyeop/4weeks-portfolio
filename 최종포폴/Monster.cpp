#include "stdafx.h"
#include "Monster.h"


Monster::Monster()
{
}


Monster::~Monster()
{
}

HRESULT Monster::init(POINT pos)
{
	bulletfire = false;
	
		return S_OK;
}

void Monster::release()
{
}

void Monster::update()
{
	
}

void Monster::render()
{
	//Rectangle(CAMERAMANAGER->getWorldDC(), monsterinfo.rc);
	/*Rectangle(CAMERAMANAGER->getWorldDC(), monsterinfo.atkRC);*/
	if(!isstoremonster)
	monsterhpBar->render(CAMERAMANAGER->getWorldDC());
	EFFECTMANAGER->render();
	
}

void Monster::Move()
{
}



bool Monster::MonsterBulletFire()
{
	if (bulletfire)
	{
		return true;
	}
	else if (!bulletfire)
	{
		return false;
	}
}

void Monster::hitDamage(float damage)
{
	monstercurrentHP -= damage;
	isHit = damage;
}

float Monster::getHP(void)
{
	
	return monstercurrentHP;
}

void Monster::MonsterRectRender()
{
	//Rectangle(CAMERAMANAGER->getWorldDC(), monsterinfo.rc);
}

