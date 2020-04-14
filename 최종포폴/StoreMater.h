#pragma once
#include "Monster.h"
class StoreMater : public Monster
{
public:
	StoreMater();
	~StoreMater();

	HRESULT init(POINT pos);
	void release();
	void update();
	void render();
	virtual void Move();

};

