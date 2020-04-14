#pragma once
#include "AllMap.h"





class InStage : public AllMap
{
public:
	InStage();
	~InStage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
private:
	
};

