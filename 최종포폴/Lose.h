#pragma once
#include "gameNode.h"
#include "button.h"
class Lose : public gameNode
{
public:
	Lose();
	~Lose();
	HRESULT init();
	void release();
	void update();
	void render();
private : 
	image* _background;
	button* startbutton;
	button* exitbotton;
	int hour, min, sec;
};

