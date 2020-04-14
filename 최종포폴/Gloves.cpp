#include "stdafx.h"
#include "Gloves.h"


Gloves::Gloves()
{
}


Gloves::~Gloves()
{
}

HRESULT Gloves::init(float posx, float posy, string img)
{
	Item::init(posx, posy, img);
	itemindex = 12;
	choiceAngle = false;
	angle = 90.f;
	gravity = 0.8f;
	Xspeed = 10.0f;
	Yspeed = 15.0f;
	price = 120;
	return S_OK;
	
}

void Gloves::release()
{
}

void Gloves::update()
{
	Item::update();
	Move();
}

void Gloves::render()
{
	Item::render();
}

void Gloves::Move()
{
	rc = RectMake(itemposX, itemposY, itemimg->getFrameWidth(), itemimg->getFrameHeight());
}
