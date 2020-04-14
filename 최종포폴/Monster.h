#pragma once
#define PI 3.14
#define DO PI/180
#include "gameNode.h"
#include "effect.h"
#include "progressBar.h"
struct tagMonster{

	POINT pos;
	RECT rc;
	RECT atkRC;
	image* img;
	int currentFrameX;
	int currentFrameY;
	int MaxframeX;
};
class Monster : public gameNode
{
public:
	Monster();
	~Monster();

	virtual HRESULT init(POINT pos);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void Move(); // ������..


	virtual void SetItemDropRc(RECT rc) { itemdroprc = rc; }
	virtual RECT GetItemDropRc() { return itemdroprc; }
	virtual void SetMapRect(RECT rc) { MapRect = rc; } // �� ��Ʈ ������
	//RECT GetMapRect() { return MapRect; }
	virtual void SetPlayerPos(float x) { PlayerPosX = x; } // ���������ȿ� ������ �� ����X����
	virtual void SetPlayerCheak(bool cheak) { playercheak = cheak; } // �÷��̾ ���������ȿ� ���Դ���
	virtual RECT GetMonsterRC() { return  monsterinfo.rc; } // ���� ��Ʈ ������
	virtual RECT GetMonsterAtkRC() { return  monsterinfo.atkRC; } // ���� ���� ��Ʈ
	virtual POINT GetMonsterPos() { return  monsterinfo.pos; }
	virtual int GetMonsterIndex() { return monsterindex; }
	virtual bool MonsterBulletFire();
	virtual float GetBulletAngle() { return bulletangle; }
	virtual void SetAngleMonsterRECT(RECT setrc) { AngleMonsterRect = setrc; } // ���ޱ۷� �Ѿ˽�ְ� �����̵��� ����
	virtual void SetAngleMonsterPlayerPosX(float playerx) { AngleMonsterPlayerPosX = playerx; }

	virtual float SetBossPlayerPos() { return skillposx; }
	virtual float GetSkillPosX() { return skillposx;}
	virtual float GetSkillPosY() { return skillposy;}
	virtual void SetBossPlayerPosX(float _X) { bossplayerposX= _X; }
	virtual void SetBossPlayerPosY(float _Y) { bossplayerposY = _Y; }
	//HP���̴� �Լ�
	virtual void hitDamage(float damage);
	virtual float getHP(void);
	//�������� HP �� ���̰�
	virtual void SetIsstoremonster(bool a) { isstoremonster = a; }

	virtual void MonsterRectRender();



protected :

	//��������
	float skillposx, skillposy;
	float bossplayerposX, bossplayerposY;


	//�Ѵ붧���� ���ǥ���̰�
	bool isstoremonster;
	//���� �ε���
	int monsterindex;
	int intervel;
	//���� ����ü
	tagMonster monsterinfo;
	//�÷��̾� ���������
	progressBar* monsterhpBar;
	//������  ,  �ִ���
	float monstercurrentHP, monstermaxHP;
	//�¾�����
	bool isHit;
	//�¾����� �ѵ��� �������̰� ���͹�
	int hitcount;
	int count;
	RECT MapRect;
	//�÷��̾� X ����
	float PlayerPosX;
	//�÷��̾ �����ȿ� ���Դ°� üũ
	bool playercheak;
	//�÷��̾ ���Դ��� Ȯ���� ����
	int range;
	// �����ΰ� �������ΰ�
	bool RL;
	// �Ѿ˹߻� 
	bool bulletfire;
	//�Ѿ� �ޱ�
	float bulletangle;
	int limitcount;
	// �پޱ� ���� ���� ����
	RECT AngleMonsterRect;
	float AngleMonsterPlayerPosX;
	RECT itemdroprc;
};

