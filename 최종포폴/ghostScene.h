#pragma once
#include "gameNode.h"
#include "knight.h"

class ghostScene : public gameNode
{
private:
	knight* _knight;

public:
	ghostScene();
	~ghostScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

