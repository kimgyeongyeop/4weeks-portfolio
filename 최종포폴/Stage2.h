#pragma once
#include "AllMap.h"

class Stage2 : public AllMap
{
public:
	Stage2();
	~Stage2();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


private:


};

