#pragma once
#include "AllMap.h"
class CharacterStage : public AllMap
{
public:
	CharacterStage();
	~CharacterStage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

private :
	image* store;
	RECT storerc;
	bool Once;
};

