#include "stdafx.h"
#include "MoneyItem.h"


MoneyItem::MoneyItem()
{
}


MoneyItem::~MoneyItem()
{
}

HRESULT MoneyItem::init(float posx, float posy, string img)
{
	Item::init(posx, posy, img);
	itemindex = 3;
	choiceAngle = false;
	angle = 0.f;
	gravity = 0.8f;
	Xspeed = 10.0f;
	Yspeed = 15.0f;
	
	return S_OK;
}

void MoneyItem::release()
{
}

void MoneyItem::update()
{
	Item::update();
	Move();
	
}

void MoneyItem::render()
{
	Item::render();
}

void MoneyItem::Move()
{
	if (!choiceAngle)
	{
		firstPosY = itemposX;
		angle = RND->getFromIntTo(85, 105);
		choiceAngle = true;
	}
	
	if (ismove)
	{
		
		itemposX -= cosf(DO*angle) * Xspeed;
		itemposY -= sinf(DO*angle) * Yspeed;
		Yspeed -= gravity;

		
	}
	rc = RectMake(itemposX, itemposY, itemimg->getFrameWidth(), itemimg->getFrameHeight());
	
}
