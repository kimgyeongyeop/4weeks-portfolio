#pragma once
#include "gameNode.h"
#include "button.h"
class StarteScene : public gameNode
{
private :
	image* _background;
	int framecount;
	int currentFrameX, currentFrameY;
	button* startbutton;
	button* optionbutton;
	button* exitbotton;
public:
	StarteScene();
	~StarteScene();

	HRESULT init();
	void release();
	void update();
	void render();

	static void ChangeStartScene();
	static void Exit();
};

