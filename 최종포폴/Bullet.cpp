#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

HRESULT Bullet::init(const char * imageName, int bulletMax, float bulletrange)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	range = bulletrange;
	currentFrameX = 0;
	currentFrameY = 0;
	return S_OK;
}

void Bullet::release()
{
}

void Bullet::update()
{
	bulletMove();

	count++;
	if (count % 10 == 0)
	{
		currentFrameX++;
		count = 0;
	}
	if (currentFrameX > 1) {

		currentFrameX = 0;

	}
}

void Bullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->bulletImage->frameRender(CAMERAMANAGER->getWorldDC(), (*_viBullet)->rc.left,
			(*_viBullet)->rc.top, currentFrameX, currentFrameY);
		//Rectangle(CAMERAMANAGER->getWorldDC(), (*_viBullet)->rc);
	}
}

void Bullet::bulletFire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vBullet.size()) return;

	myBullet = new tagBullet;
	myBullet->bulletImage = IMAGEMANAGER->findImage(_imageName);
	myBullet->x = myBullet->fireX = x;
	myBullet->y = myBullet->fireY = y;
	myBullet->angle = angle;
	myBullet->speed = speed;
	//ÃÑ¾Ë°¢µµ¿¡ µû¸¥ ÃÑ¾ËÇÁ·¹ÀÓ¹Ù²ãÁÜ
	if (myBullet->angle  < 90*DO && myBullet->angle > -90*DO )
	{
		currentFrameY = 1;
	}
	else if (myBullet->angle >= 90*DO && myBullet->angle<= 270 * DO)
	{
		currentFrameY = 0;
	}

	myBullet->rc = RectMakeCenter(myBullet->x, myBullet->y,
		myBullet->bulletImage->getFrameWidth(),
		myBullet->bulletImage->getFrameHeight());

	_vBullet.push_back(myBullet);

}

void Bullet::bulletMove()
{
	
	

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
	{
		if (_vBullet.size() <= 0) return;


		


		(*_viBullet)->x += cosf((*_viBullet)->angle) * (*_viBullet)->speed;
		(*_viBullet)->y += -sinf((*_viBullet)->angle) * (*_viBullet)->speed;

		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->bulletImage->getFrameWidth(),
			(*_viBullet)->bulletImage->getFrameHeight());

		if (range < getDistance((*_viBullet)->fireX, (*_viBullet)->fireY,
			(*_viBullet)->x, (*_viBullet)->y))
		{
			_vBullet.erase(_viBullet);
			break;
		}
		else
		{
			++_viBullet;
		}
		
		
	}
}

void Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
