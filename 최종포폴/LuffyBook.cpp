#include "stdafx.h"
#include "LuffyBook.h"


LuffyBook::LuffyBook()
{
}


LuffyBook::~LuffyBook()
{
}

HRESULT LuffyBook::init(float posx, float posy, string img)
{
	Item::init(posx, posy, img);
	
	itemindex = 5;
	choiceAngle = false;
	angle = 90.f;
	gravity = 0.8f;
	Xspeed = 10.0f;
	Yspeed = 15.0f;
	return S_OK;
}

void LuffyBook::release()
{
}

void LuffyBook::update()
{
	Item::update();

	Move();
}

void LuffyBook::render()
{
	Item::render();
}

void LuffyBook::Move()
{
	if (ismove)
	{
		itemposX -= cosf(DO*angle) * Xspeed;
		itemposY -= sinf(DO*angle) * Yspeed;
		Yspeed -= gravity;


		
	}
	rc = RectMake(itemposX, itemposY, itemimg->getFrameWidth(), itemimg->getFrameHeight());
}
