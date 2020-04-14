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
	virtual void Move(); // 움직임..


	virtual void SetItemDropRc(RECT rc) { itemdroprc = rc; }
	virtual RECT GetItemDropRc() { return itemdroprc; }
	virtual void SetMapRect(RECT rc) { MapRect = rc; } // 맵 렉트 가져옴
	//RECT GetMapRect() { return MapRect; }
	virtual void SetPlayerPos(float x) { PlayerPosX = x; } // 추적범위안에 들어왔을 때 몬스터X추적
	virtual void SetPlayerCheak(bool cheak) { playercheak = cheak; } // 플레이어가 추적범위안에 들어왔는지
	virtual RECT GetMonsterRC() { return  monsterinfo.rc; } // 몬스터 렉트 보내줌
	virtual RECT GetMonsterAtkRC() { return  monsterinfo.atkRC; } // 몬스터 공격 렉트
	virtual POINT GetMonsterPos() { return  monsterinfo.pos; }
	virtual int GetMonsterIndex() { return monsterindex; }
	virtual bool MonsterBulletFire();
	virtual float GetBulletAngle() { return bulletangle; }
	virtual void SetAngleMonsterRECT(RECT setrc) { AngleMonsterRect = setrc; } // 갯앵글로 총알쏠애가 순간이동할 발판
	virtual void SetAngleMonsterPlayerPosX(float playerx) { AngleMonsterPlayerPosX = playerx; }

	virtual float SetBossPlayerPos() { return skillposx; }
	virtual float GetSkillPosX() { return skillposx;}
	virtual float GetSkillPosY() { return skillposy;}
	virtual void SetBossPlayerPosX(float _X) { bossplayerposX= _X; }
	virtual void SetBossPlayerPosY(float _Y) { bossplayerposY = _Y; }
	//HP깍이는 함수
	virtual void hitDamage(float damage);
	virtual float getHP(void);
	//상점주인 HP 바 보이게
	virtual void SetIsstoremonster(bool a) { isstoremonster = a; }

	virtual void MonsterRectRender();



protected :

	//보스전용
	float skillposx, skillposy;
	float bossplayerposX, bossplayerposY;


	//한대때리면 목숨표보이게
	bool isstoremonster;
	//몬스터 인덱스
	int monsterindex;
	int intervel;
	//몬스터 구조체
	tagMonster monsterinfo;
	//플레이어 목숨게이지
	progressBar* monsterhpBar;
	//현재목숨  ,  최대목숨
	float monstercurrentHP, monstermaxHP;
	//맞았을때
	bool isHit;
	//맞았을때 한동안 못움직이게 인터벌
	int hitcount;
	int count;
	RECT MapRect;
	//플레이어 X 추적
	float PlayerPosX;
	//플레이어가 범위안에 들어왔는가 체크
	bool playercheak;
	//플레이어가 들어왔는지 확인할 범위
	int range;
	// 왼쪽인가 오른쪽인가
	bool RL;
	// 총알발사 
	bool bulletfire;
	//총알 앵글
	float bulletangle;
	int limitcount;
	// 겟앵글 몬스터 전용 변수
	RECT AngleMonsterRect;
	float AngleMonsterPlayerPosX;
	RECT itemdroprc;
};

