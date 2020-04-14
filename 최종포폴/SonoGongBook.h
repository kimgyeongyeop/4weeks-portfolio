#pragma once
#include "Item.h"
class SonoGongBook : public Item
{
public:
	SonoGongBook();
	~SonoGongBook();

	virtual HRESULT init(float posx, float posy, string img);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void Move(); // ¿òÁ÷ÀÓ..
};

