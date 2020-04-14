#include "stdafx.h"
#include "Marble.h"


Marble::Marble()
{
}


Marble::~Marble()
{
}

HRESULT Marble::init(float posx, float posy, string img)
{
	Item::init(posx, posy, img);
	itemindex = 13;
	choiceAngle = false;
	angle = 90.f;
	gravity = 0.8f;
	Xspeed = 10.0f;
	Yspeed = 15.0f;
	price = 130;
	return S_OK;
}

void Marble::release()
{
}

void Marble::update()
{
	Item::update();
	Move();
}

void Marble::render()
{
	Item::render();
}

void Marble::Move()
{
	rc = RectMake(itemposX, itemposY, itemimg->getFrameWidth(), itemimg->getFrameHeight());
}
