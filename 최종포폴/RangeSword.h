#pragma once
#include "Item.h"
class RangeSword : public Item
{
public:
	RangeSword();
	~RangeSword();

	virtual HRESULT init(float posx, float posy, string img);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void Move(); // ������..
};

