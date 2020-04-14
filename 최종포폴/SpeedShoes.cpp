#include "stdafx.h"
#include "SpeedShoes.h"


SpeedShoes::SpeedShoes()
{
}


SpeedShoes::~SpeedShoes()
{
}

HRESULT SpeedShoes::init(float posx, float posy, string img)
{
	Item::init(posx, posy, img);
	itemindex = 9;
	choiceAngle = false;
	angle = 90.f;
	gravity = 0.8f;
	Xspeed = 10.0f;
	Yspeed = 15.0f;
	price = 134;
	return S_OK;
}

void SpeedShoes::release()
{
}

void SpeedShoes::update()
{
	Item::update();
	Move();
}

void SpeedShoes::render()
{
	Item::render();
}

void SpeedShoes::Move()
{
	rc = RectMake(itemposX, itemposY, itemimg->getFrameWidth(), itemimg->getFrameHeight());
}
