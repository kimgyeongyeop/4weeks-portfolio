#include "stdafx.h"
#include "HpItem.h"



HpItem::HpItem()
{
}


HpItem::~HpItem()
{
}

HRESULT HpItem::init(float posx, float posy, string img)
{
	Item::init(posx, posy, img);
	itemindex = 1;
	choiceAngle = false;
	angle = 90.f;
	gravity = 0.8f;
	Xspeed = 10.0f;
	Yspeed = 15.0f;
	price = 60;
	return S_OK;
}

void HpItem::release()
{
}

void HpItem::update()
{
	Item::update();
	Move();
}

void HpItem::render()
{
	Item::render();
}

void HpItem::Move()
{
	if (ismove)
	{
	itemposX -= cosf(DO*angle) * Xspeed;
	itemposY -= sinf(DO*angle) * Yspeed;
	Yspeed -= gravity;


	
	}
	rc = RectMake(itemposX, itemposY, itemimg->getFrameWidth(), itemimg->getFrameHeight());
}
