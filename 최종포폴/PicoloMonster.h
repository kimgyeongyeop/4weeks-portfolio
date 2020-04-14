#pragma once
#include "Monster.h"

class PicoloMonster : public Monster
{
public:
	PicoloMonster();
	~PicoloMonster();

	HRESULT init(POINT pos);
	void release();
	void update();
	void render();
	virtual void Move();
	
private:
	
	bool RL;
};

