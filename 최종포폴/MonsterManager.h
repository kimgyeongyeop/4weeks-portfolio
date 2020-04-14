#pragma once

#include "gameNode.h"
#include <vector>
#include "Bullet.h"
#include "BasicMonster.h"
#include "FlowerMonster.h"
#include "PicoloMonster.h"
#include "PoisonMonster.h"
#include "PirateMonster.h"
#include "NavyMonster.h"
#include "GetAngleMonster.h"
#include "Boss.h"

class Player;

class MonsterManager : public gameNode
{
public:
	MonsterManager();
	~MonsterManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void RemoveMonster(int arr);
	void set_BasicMonster(POINT mosterpos);
	void set_FlowerMonster(POINT mosterpos);
	void set_PicoloMonster(POINT mosterpos);
	void set_PoisonMonster(POINT mosterpos);
	void set_PirateMonster(POINT mosterpos);
	void set_NavyMonster(POINT mosterpos);
	void set_GetAngleMonster(POINT mosterpos);
	void set_Boss(POINT mosterpos);

	void MonsterBulletFire();
	void Collision();
	vector<Monster*> getVmonster() { return _vMonster; }
	vector<Monster*>::iterator getVimonster() { return _viMonster; }
	void setPlayerMemoryAddressLink(Player* player) { _player = player; }
private:
	Player* _player;
	Bullet* monster2bullet;
	Bullet* monster3bullet;
	Bullet* monster5bullet;
	Bullet* monster7bullet;
	Bullet* bossbullet;
	vector<Monster*>           _vMonster;
	vector<Monster*>::iterator _viMonster;
	float angle;
};

