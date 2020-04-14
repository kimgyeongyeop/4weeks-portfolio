#include "stdafx.h"
#include "NarutoBook.h"


NarutoBook::NarutoBook()
{
}


NarutoBook::~NarutoBook()
{
}

HRESULT NarutoBook::init(float posx, float posy, string img)
{
	Item::init(posx, posy, img);
	
	itemindex = 4;
	choiceAngle = false;
	angle = 90.f;
	gravity = 0.8f;
	Xspeed = 10.0f;
	Yspeed = 15.0f;
	return S_OK;
	
}

void NarutoBook::release()
{
}

void NarutoBook::update()
{
	Item::update();
	
	Move();
}

void NarutoBook::render()
{
	Item::render();
}

void NarutoBook::Move()
{
	if (ismove)
	{
		itemposX -= cosf(DO*angle) * Xspeed;
		itemposY -= sinf(DO*angle) * Yspeed;
		Yspeed -= gravity;


		
	}
	rc = RectMake(itemposX, itemposY, itemimg->getFrameWidth(), itemimg->getFrameHeight());
}
