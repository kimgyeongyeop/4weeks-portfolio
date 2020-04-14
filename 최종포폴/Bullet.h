#pragma once
#define DO PI/180
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float angle;
	float radius;
	float speed;
	float fireX, fireY;
	
	bool isFire;
};

class Bullet : public gameNode
{
public:
	Bullet();
	~Bullet();

	HRESULT init(const char* imageName, int bulletMax, float bulletrange);
	void release();
	void update();
	void render();
	void bulletFire(float x, float y, float angle, float speed);
	void bulletMove();
	void removeBullet(int arrNum);

	vector<tagBullet*> getVBullet() { return _vBullet; }
	vector<tagBullet*>::iterator getViBullet() { return _viBullet; }

private:
	int currentFrameX;
	int currentFrameY;
	tagBullet* myBullet;
	const char* _imageName;
	int _bulletMax;
	float range;
	int count;
	vector<tagBullet*>			_vBullet;
	vector<tagBullet*>::iterator _viBullet;
};

