#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	float _x, _y;
	float _width;

	image* _progressBarTop;			//������ �տ� �̹���
	image* _progressBarBottom;		//������ �ڿ� �̹���

public:
	progressBar();
	~progressBar();

	virtual HRESULT init(string name, float x, float y, int width, int height);
	virtual void release();
	virtual void update();
	virtual void render(HDC a);

	void setGauge(float currentGauge, float maxGauge);

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
};

