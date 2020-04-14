#pragma once
#include "gameNode.h"
#include "tankMap.h"

enum TANKDIRECTION
{
	TANKDIRECTION_LEFT,
	TANKDIRECTION_TOP,
	TANKDIRECTION_RIGHT,
	TANKDIRECTION_BOTTOM
};

class tank : public gameNode
{
private:
	tankMap* _tankMap;
	image* _image;
	float _x, _y;
	float _speed;
	RECT _rc;
	TANKDIRECTION _direction;

public:
	tank();
	~tank();

	HRESULT init();
	void release();
	void update();
	void render();

	void tankMove();
	void setTankPosition();

	void setTankMapMemoryAddressLink(tankMap* tm) { _tankMap = tm; }
};

