#include "stdafx.h"
#include "HeadPiece.h"


HeadPiece::HeadPiece()
{
}


HeadPiece::~HeadPiece()
{
}

HRESULT HeadPiece::init(float posx, float posy, string img)
{
	Item::init(posx, posy, img);
	itemindex = 7;
	choiceAngle = false;
	angle = 90.f;
	gravity = 0.8f;
	Xspeed = 10.0f;
	Yspeed = 15.0f;
	price = 130;
	return S_OK;
}

void HeadPiece::release()
{
}

void HeadPiece::update()
{
	Item::update();
	Move();
}

void HeadPiece::render()
{
	Item::render();
}

void HeadPiece::Move()
{
	
	rc = RectMake(itemposX, itemposY, itemimg->getFrameWidth(), itemimg->getFrameHeight());
}
