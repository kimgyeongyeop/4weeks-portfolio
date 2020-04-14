#pragma once
#include "gameNode.h"
#include "button.h"
#include "action.h"

static image* testImage = NULL;
static action* actionTest;

class selectScene : public gameNode
{
private:
	button* _btnSceneChange;

	action* _actionTest;

public:
	selectScene();
	~selectScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	static void cbSceneChange();

	static void cbAction();
};

