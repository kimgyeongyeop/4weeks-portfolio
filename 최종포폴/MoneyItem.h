#pragma once
#include "Item.h"
class MoneyItem : public Item
{
public:
	MoneyItem();
	~MoneyItem();

	virtual HRESULT init(float posx, float posy, string img);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void Move(); // ¿òÁ÷ÀÓ..



private:
	
};

