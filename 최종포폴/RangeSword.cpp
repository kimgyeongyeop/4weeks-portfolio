#include "stdafx.h"
#include "RangeSword.h"


RangeSword::RangeSword()
{
}


RangeSword::~RangeSword()
{
}

HRESULT RangeSword::init(float posx, float posy, string img)
{
	Item::init(posx, posy, img);
	itemindex = 11;
	choiceAngle = false;
	angle = 90.f;
	gravity = 0.8f;
	Xspeed = 10.0f;
	Yspeed = 15.0f;
	price = 95;
	return S_OK;
}

void RangeSword::release()
{
}

void RangeSword::update()
{
	Item::update();
	Move();
}

void RangeSword::render()
{
	Item::render();
}

void RangeSword::Move()
{
	rc = RectMake(itemposX, itemposY, itemimg->getFrameWidth(), itemimg->getFrameHeight());
}
