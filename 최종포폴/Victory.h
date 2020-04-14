#pragma once
#include "gameNode.h"
#include "button.h"
class Victory : public gameNode
{
private:
	image* _background;
	button* startbutton;
	button* exitbotton;
	int hour,min,sec;
public:
	Victory();
	~Victory();


	HRESULT init();
	void release();
	void update();
	void render();

	
};

