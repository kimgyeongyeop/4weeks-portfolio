#pragma once
#include "AllMap.h"

class Stage4 : public AllMap
{
public:
	Stage4();
	~Stage4();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

