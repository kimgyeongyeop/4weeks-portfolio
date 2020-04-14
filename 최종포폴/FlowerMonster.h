#pragma once
#include "Monster.h"
class FlowerMonster : public Monster
{
public:
	FlowerMonster();
	~FlowerMonster();

	virtual HRESULT init(POINT pos);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void Move();
	
private :
		
};

