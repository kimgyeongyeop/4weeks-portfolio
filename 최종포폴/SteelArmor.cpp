#include "stdafx.h"
#include "SteelArmor.h"


SteelArmor::SteelArmor()
{
}


SteelArmor::~SteelArmor()
{
}

HRESULT SteelArmor::init(float posx, float posy, string img)
{
	Item::init(posx, posy, img);
	itemindex = 8;
	choiceAngle = false;
	angle = 90.f;
	gravity = 0.8f;
	Xspeed = 10.0f;
	Yspeed = 15.0f;
	price = 150;
	return S_OK;
}

void SteelArmor::release()
{
}

void SteelArmor::update()
{
	Item::update();
	Move();
}

void SteelArmor::render()
{
	Item::render();
}

void SteelArmor::Move()
{
	rc = RectMake(itemposX, itemposY, itemimg->getFrameWidth(), itemimg->getFrameHeight());
}
