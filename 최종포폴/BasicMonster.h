#pragma once
#include "Monster.h"
class BasicMonster : public Monster
{
public:
	BasicMonster();
	~BasicMonster();

	HRESULT init(POINT pos);
	void release();
	void update();
	void render();
	virtual void Move();
	

private :
	
};

