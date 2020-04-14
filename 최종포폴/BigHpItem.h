#pragma once
#include "Item.h"
class BigHpItem : public Item
{
public:
	BigHpItem();
	~BigHpItem();

	virtual HRESULT init(float posx, float posy, string img);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void Move(); // ¿òÁ÷ÀÓ..
};

