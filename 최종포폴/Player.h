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

	//�ŷ����
	void SetDragon();

	//���ͼ���

	

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
	//����� rc
	RECT GetPlayerOnegiRC() { return Onegirc; }
	//�÷��̾� ��ų�ε���
	int GetSkiilIndex() { return _player.skillindex; }
	// ���ȴ���Ȯ��
	void SetIsHit(bool a) { ishit = a; }
	// �¾Ҵ��� Ȯ��
	void SetSetHit(bool a) { issethit = a; }
	//Ŀ�ǵ��������Ȯ��
	bool GetIsCommand() {return _player.isCommand;}
	void SetIsCommand(bool a) { _player.isCommand = a; }

	RECT GetPlayerSkillRc() { return _player.skillrc; }
	int GetPlayerPcType() { return (int)PC; }

	bool GetPlayerRL() { return RL; }
	
	//���Ͱ� �÷��̾� ��������
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
	//��ų

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
	//��������������������������⺻�÷��̾� �̹�������������������������
	image* basicplayer;
	
	animation* BasicPlayerAni;
	image* skillimg;
	//�������� �̹���
	image* backenergy;
	image* frontenergy;
	image* Dragon;
	int Scnt, FrameX;
	bool Fexit;
	int energyrange;
	int energysizex;
	bool isrightenergy;
	bool isleftenergy;
	//true�� ��ų�ߵ�
	bool isskill;
	//�����ʿ��� �Ǻ� �����̸� false �������̸� true
	bool RL;
	int arr[5];

	int currentFrameX;
	int currentFrameY;
	int MaxFrameX;

	int hitframecount;
	
	int hitcurrentFrameX;
	int hitcurrentFrameY;


};


//�÷��̾� ����

//class PlayerStateBase
//{
//public:
//	PlayerStateBase(Player* p)
//		:me(p) {}
//	virtual void Enter() = 0;
//	virtual void Update() = 0;
//protected:
//	Player* me; // ����Ѵ� MonsterŬ���� me ���� ���
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

