#pragma once
#include "Item.h"
class PowerSword : public Item
{
public:
	PowerSword();
	~PowerSword();

	virtual HRESULT init(float posx, float posy, string img);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void Move(); // ¿òÁ÷ÀÓ..
};

