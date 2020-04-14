#pragma once
#include "gameNode.h"




struct _tagPlayera
{
	POINTFLOAT center;
	RECT	   rc;
	RECT       floorrc;
	bool isground;
	bool isjump;
	
	image* _ATOM;
};

struct _mapObja
{
	RECT	   rc;
	bool collion;
};
class inGameScene : public gameNode
{

	friend class PlayerBase;
	friend class PlayerIdle;
	friend class PlayerJump;
	friend class PlayerAir;

public:
	inGameScene();
	~inGameScene();

	HRESULT init();
	void release();
	void update();
	void render();
	void Gravity(); //�׻� ���̾ƴϸ� �߷� ����
	void CheakLocation();
	void ChangeState(string key);
private:
	float jumppower, gravitiy;
		//���浹��Ʈ��
	
	int jumpcount;
	_mapObja maprc[9];
	
	image*	bg[3];

	

	_tagPlayera _player;

	

	
	image* _MAP;

	map<string, class PlayerBase*> states;
	PlayerBase* currentState;
	int blocktype;
};




class PlayerBase
{
public:
	PlayerBase(inGameScene* p)
		:me(p) {}
	virtual void Enter() = 0;
	virtual void Update() = 0;
protected:
	inGameScene* me; // ����Ѵ� MonsterŬ���� me ���� ���
};

class PlayerIdle : public PlayerBase
{
public:
	PlayerIdle(inGameScene* p) : PlayerBase(p) {}
	virtual void Enter();
	virtual void Update();
private:

};

class PlayerJump : public PlayerBase
{
public:
	PlayerJump(inGameScene* p) : PlayerBase(p) {}
	virtual void Enter();
	virtual void Update();
private:

};


class PlayerAir : public PlayerBase
{
public:
	PlayerAir(inGameScene* p) : PlayerBase(p) {}
	virtual void Enter();
	virtual void Update();
private:
};