#pragma once
#include "Monster.h"
class GetAngleMonster : public Monster
{
public:
	GetAngleMonster();
	~GetAngleMonster();

	HRESULT init(POINT pos);
	void release();
	void update();
	void render();
	virtual void Move();

private:

	int bulletdelaytime;
	int imgY;
	bool RL;
};

