#pragma once
#include "AllMap.h"

class BossMap : public AllMap
{
public:
	BossMap();
	~BossMap();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

private :
	int alphavalue;
	bool isdark;
};

