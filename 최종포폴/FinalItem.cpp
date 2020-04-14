#include "stdafx.h"
#include "FinalItem.h"


FinalItem::FinalItem()
{
}


FinalItem::~FinalItem()
{
}

HRESULT FinalItem::init(float posx, float posy, string img)
{
	Item::init(posx, posy, img);

	itemindex = 14;
	choiceAngle = false;
	angle = 90.f;
	gravity = 0.8f;
	Xspeed = 10.0f;
	Yspeed = 15.0f;
	return S_OK;
}

void FinalItem::release()
{
}

void FinalItem::update()
{
	Item::update();

	Move();
}

void FinalItem::render()
{
	Item::render();
}

void FinalItem::Move()
{
	if (ismove)
	{
		itemposX -= cosf(DO*angle) * Xspeed;
		itemposY -= sinf(DO*angle) * Yspeed;
		Yspeed -= gravity;



	}
	rc = RectMake(itemposX, itemposY, itemimg->getFrameWidth(), itemimg->getFrameHeight());
}
