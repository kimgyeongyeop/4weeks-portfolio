#pragma once
#include "Item.h"
class SpeedShoes : public Item
{
public:
	SpeedShoes();
	~SpeedShoes();

	virtual HRESULT init(float posx, float posy, string img);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void Move(); // ¿òÁ÷ÀÓ..
};

