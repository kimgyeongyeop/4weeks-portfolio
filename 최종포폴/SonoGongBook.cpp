#include "stdafx.h"
#include "SonoGongBook.h"


SonoGongBook::SonoGongBook()
{
}


SonoGongBook::~SonoGongBook()
{
}

HRESULT SonoGongBook::init(float posx, float posy, string img)
{
	Item::init(posx, posy, img);
	
	itemindex = 6;
	choiceAngle = false;
	angle = 90.f;
	gravity = 0.8f;
	Xspeed = 10.0f;
	Yspeed = 15.0f;
	return S_OK;
}

void SonoGongBook::release()
{
}

void SonoGongBook::update()
{
	Item::update();

	Move();
}

void SonoGongBook::render()
{
	Item::render();
}

void SonoGongBook::Move()
{
	if (ismove)
	{
		itemposX -= cosf(DO*angle) * Xspeed;
		itemposY -= sinf(DO*angle) * Yspeed;
		Yspeed -= gravity;


		
	}
	rc = RectMake(itemposX, itemposY, itemimg->getFrameWidth(), itemimg->getFrameHeight());
}
