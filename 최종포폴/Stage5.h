#pragma once
#include "AllMap.h"
class Stage5 : public AllMap
{
public:
	Stage5();
	~Stage5();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

