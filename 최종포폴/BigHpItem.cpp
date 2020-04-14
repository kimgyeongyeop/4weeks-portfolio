#include "stdafx.h"
#include "BigHpItem.h"


BigHpItem::BigHpItem()
{
}


BigHpItem::~BigHpItem()
{
}

HRESULT BigHpItem::init(float posx, float posy, string img)
{
	Item::init(posx, posy, img);
	itemindex = 2;
	choiceAngle = false;
	angle = 90.f;
	gravity = 0.8f;
	Xspeed = 10.0f;
	Yspeed = 15.0f;
	price = 100;
	return S_OK;
}

void BigHpItem::release()
{
}

void BigHpItem::update()
{
	Item::update();
	Move();
}

void BigHpItem::render()
{
	Item::render();
}

void BigHpItem::Move()
{
	if (ismove)
	{
		itemposX -= cosf(DO*angle) * Xspeed;
		itemposY -= sinf(DO*angle) * Yspeed;
		Yspeed -= gravity;


		
	}
	rc = RectMake(itemposX, itemposY, itemimg->getFrameWidth(), itemimg->getFrameHeight());
}
