#pragma once
#include "AllMap.h"




class Stage1 : public AllMap
{
public:
	Stage1();
	~Stage1();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
private:
	
};

