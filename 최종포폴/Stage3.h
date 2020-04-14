#pragma once
#include "AllMap.h"
class Stage3 : public AllMap
{
public:
	Stage3();
	~Stage3();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

