#pragma once
#include "Monster.h"
class Boss : public Monster
{

	friend class StateBase;
	friend class Idle;
	friend class Skill1;
	friend class Skill2;
	friend class Skill3;
	friend class Skill4;
	friend class Skill5;
public:
	Boss();
	~Boss();
	HRESULT init(POINT pos);
	void release();
	void update();
	void render();
	
	void frame();
	void prograssbar();


	void ChangeState(string key);
	


private :
	map<string, class StateBase*> states;
	StateBase* currentState;
	int skillintervel;

	int Inskillintervel;
	int errorX, errorY;
	int random;
	bool isstartskill;
	bool isendskill;
	int skillcount;
	int skillframecurenntX;
	int skillframecurenntY;
	float tempplayerposx, tempplayerposy;
	image* skillimg;
	
};


class StateBase
{
public:
	StateBase(Boss* p)
		:me(p) {}
	virtual void Enter() = 0;
	virtual void Update() = 0;
protected:
	Boss* me; // 상속한다 Monster클래스 me 값을 상속
};


class Idle : public StateBase
{
public:
	Idle(Boss* p) : StateBase(p) {}
	virtual void Enter();
	virtual void Update();
private:

};


class Skill1 : public StateBase
{
public:
	Skill1(Boss* p) : StateBase(p) {}
	virtual void Enter();
	virtual void Update();
private:

};

class Skill2 : public StateBase
{
public:
	Skill2(Boss* p) : StateBase(p) {}
	virtual void Enter();
	virtual void Update();
private:

};

class Skill3 : public StateBase
{
public:
	Skill3(Boss* p) : StateBase(p) {}
	virtual void Enter();
	virtual void Update();
private:

};

class Skill4 : public StateBase
{
public:
	Skill4(Boss* p) : StateBase(p) {}
	virtual void Enter();
	virtual void Update();
private:
};


class Skill5 : public StateBase
{
public:
	Skill5(Boss* p) : StateBase(p) {}
	virtual void Enter();
	virtual void Update();
private:

};