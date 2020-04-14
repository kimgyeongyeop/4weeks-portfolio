#pragma once
#include "AllMap.h"
class ShopStage : public AllMap
{
public:
	ShopStage();
	~ShopStage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

private :
	
};

