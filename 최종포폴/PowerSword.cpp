#include "stdafx.h"
#include "PowerSword.h"


PowerSword::PowerSword()
{
}


PowerSword::~PowerSword()
{
}

HRESULT PowerSword::init(float posx, float posy, string img)
{
	Item::init(posx, posy, img);
	itemindex = 10;
	choiceAngle = false;
	angle = 90.f;
	gravity = 0.8f;
	Xspeed = 10.0f;
	Yspeed = 15.0f;
	price = 109;
	return S_OK;
}

void PowerSword::release()
{
}

void PowerSword::update()
{
	Item::update();
	Move();
}

void PowerSword::render()
{
	Item::render();
}

void PowerSword::Move()
{
	rc = RectMake(itemposX, itemposY, itemimg->getFrameWidth(), itemimg->getFrameHeight());
}
