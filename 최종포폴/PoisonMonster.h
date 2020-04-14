#pragma once
#include "Monster.h"
class PoisonMonster : public Monster
{
public:
	PoisonMonster();
	~PoisonMonster();

	HRESULT init(POINT pos);
	void release();
	void update();
	void render();
	virtual void Move();
	
private:
};

