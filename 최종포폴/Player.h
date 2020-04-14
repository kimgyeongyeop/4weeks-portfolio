#pragma once
#include "gameNode.h"
#include "effect.h"
#include "ItemManager.h"
#include "Bullet.h"
class MonsterManager;

enum PlayerCharacters
{
	BASIC,
	NARUTO,
	LUFFY,
	SONOGONG

};


enum PlayerState
{
	PLAYER_LEFT_IDLE,
	PLAYER_RIGHT_IDLE,
	PLAYER_LEFT_MOVE,
	PLAYER_RIGHT_MOVE,
	PLAYER_LEFT_JUMP,
	PLAYER_RIGHT_JUMP,
	PLAYER_LEFT_ATK,
	PLAYER_RIGHT_ATK,
};



struct _tagPlayer
{
	POINTFLOAT center;
	RECT	   rc;
	RECT       atkrc;
	RECT skillrc;
	bool isground;
	bool isjump;
	image* playerimg;
	
	bool isCommand;
	int skillindex;
	float speed;
};

class Player : public gameNode
{

	/*friend class PlayerStateBase;
	friend class PlayerNaruto;
	friend class PlayerLuffy;
*/
public:
	Player();
	~Player();

	HRESULT init();
	void release();
	void update();
	void render();
	void Gravity();
	void Player_Controll();
	void Player_State();
	void MonsterCollison();
	void PlayerAndItemCollison();
	void WindowMapCollison();
	/*void ChangeState(string key);*/
	void PlayerTypeChange();
	void SkillFrame();
	void SettingSkillImg(string skillname, int _currentFrameX, int _currentFrameY, int _MaxFrameX, bool _isskill);
	void EndSkillRect();
	void OneGi();

	//신룡재생
	void SetDragon();

	//겟터셋터

	

	void SetGravitiy(bool on) { _player.isground = on; }
	void SetIsJump(bool on) { _player.isjump = on; }
	void SetJumpPower(float Jumppower) { jumppower = Jumppower; }
	RECT GetPlayerRC() { return _player.rc; }
	RECT GetPlayerAtkRC() { return _player.atkrc; }
	void SetAtkRC(RECT a) { _player.atkrc =a; }

	void SetPlayerRCBottom(int rc) { _player.rc.bottom = rc; }
	void SetPlayerY(float Y) { _player.center.y = Y; }
	void SetPlayerX(float X) { _player.center.x = X; }
	void SetJumpCount(int count) { jumpcount = count; }
	float GetPlayerX() { return _player.center.x; }
	float GetPlayerY() { return _player.center.y; }
	int GetPlayerType() { return playertype;}
	//원기옥 rc
	RECT GetPlayerOnegiRC() { return Onegirc; }
	//플레이어 스킬인덱스
	int GetSkiilIndex() { return _player.skillindex; }
	// 때렸는지확인
	void SetIsHit(bool a) { ishit = a; }
	// 맞았는지 확인
	void SetSetHit(bool a) { issethit = a; }
	//커맨드공격인지확인
	bool GetIsCommand() {return _player.isCommand;}
	void SetIsCommand(bool a) { _player.isCommand = a; }

	RECT GetPlayerSkillRc() { return _player.skillrc; }
	int GetPlayerPcType() { return (int)PC; }

	bool GetPlayerRL() { return RL; }
	
	//몬스터가 플레이어 가져가자
	void setMemoryAddressLink(MonsterManager* MonsterMG) { _monsterMG = MonsterMG; }
private:
	bool issethit;
	image* hitimg;

	Bullet* narutoBullet;
	Bullet* itemBullet;
	image* Onegi;
	bool isOnegi;
	int OnegiframeX;
	RECT Onegirc;
	
	int Onegicount;

	bool ishit;
	//스킬

	int atktime;
	int framecount;
	int playertype;
	
	int anicount;
	float jumppower, gravitiy, sumgravity;
	int jumpcount;
	int type;
	_tagPlayer _player;

	MonsterManager* _monsterMG;
	ItemManager* _itemMG;
	PlayerState PS;

	PlayerCharacters PC;

	int errorX, errorY;


	/*PlayerStateBase* currentState;
	map<string, class PlayerStateBase*> states;*/
	//■■■■■■■■■■■■■■■■■■■■■■■■■기본플레이어 이미지■■■■■■■■■■■■■■■■■■■■■
	image* basicplayer;
	
	animation* BasicPlayerAni;
	image* skillimg;
	//에너지파 이미지
	image* backenergy;
	image* frontenergy;
	image* Dragon;
	int Scnt, FrameX;
	bool Fexit;
	int energyrange;
	int energysizex;
	bool isrightenergy;
	bool isleftenergy;
	//true면 스킬발동
	bool isskill;
	//오른쪽왼쪽 판별 왼쪽이면 false 오른쪽이면 true
	bool RL;
	int arr[5];

	int currentFrameX;
	int currentFrameY;
	int MaxFrameX;

	int hitframecount;
	
	int hitcurrentFrameX;
	int hitcurrentFrameY;


};


//플레이어 상태

//class PlayerStateBase
//{
//public:
//	PlayerStateBase(Player* p)
//		:me(p) {}
//	virtual void Enter() = 0;
//	virtual void Update() = 0;
//protected:
//	Player* me; // 상속한다 Monster클래스 me 값을 상속
//};
//
//class PlayerNaruto : public PlayerStateBase
//{
//public:
//	PlayerNaruto(Player* p) : PlayerStateBase(p) {}
//	virtual void Enter();
//	virtual void Update();
//private:
//
//};
//
//class PlayerLuffy : public PlayerStateBase
//{
//public:
//	PlayerLuffy(Player* p) : PlayerStateBase(p) {}
//	virtual void Enter();
//	virtual void Update();
//private:
//
//};

