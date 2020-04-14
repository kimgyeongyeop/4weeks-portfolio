#pragma once
#include "Item.h"
class SteelArmor : public Item
{
public:
	SteelArmor();
	~SteelArmor();

	virtual HRESULT init(float posx, float posy, string img);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void Move(); // ¿òÁ÷ÀÓ..
};

