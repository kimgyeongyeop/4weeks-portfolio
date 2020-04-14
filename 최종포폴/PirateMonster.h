#pragma once
#include "Monster.h"
class PirateMonster : public Monster
{
public:
	PirateMonster();
	~PirateMonster();

	HRESULT init(POINT pos);
	void release();
	void update();
	void render();
	virtual void Move();

private:

};

