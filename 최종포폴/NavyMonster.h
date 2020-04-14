#pragma once
#include "Monster.h"
class NavyMonster : public Monster
{

public:
	NavyMonster();
	~NavyMonster();

	HRESULT init(POINT pos);
	void release();
	void update();
	void render();
	virtual void Move();


private:
	bool RL;
};

