#pragma once
#include "Item.h"
class FinalItem : public Item
{
public:
	FinalItem();
	~FinalItem();

	virtual HRESULT init(float posx, float posy, string img);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void Move(); // ������..
};

