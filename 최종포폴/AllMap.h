#pragma once
#include "gameNode.h"
#include "Player.h"
#include "MonsterManager.h"
#include "ItemManager.h"
#include "UiManager.h"
class Player;
class MonsterManager;
class GameData;



struct _mapObj
{
	RECT	   rc;
	bool collion;
};

class AllMap : public gameNode
{
public:
	AllMap();
	~AllMap();

	static GameData* gameData;
	static GameData* GetData();


	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	//맵에 좌표 알아오는 함수
	virtual void CheakLocation();
	//플레이어랑 맵 충돌함수
	virtual void PlayerAndMapCollion(int groundRECT, int leftRECT, int rightRECT);
	//몬스터랑 맵 충돌함수
	virtual void MonsterAndMapCollion(int groundRECT);
	//몬스터랑 플레이어 충돌
	virtual void MonsterAndPlayerCollion();
	//플레이어랑 아이템 충돌 
	virtual void PlayerAndItemCollion();
	//땅 렉트 그려보는함수
	virtual void GroundRectRender(int groundRECT);
	//오른쪽 벽 렉트그려보는함수
	virtual void LeftRectRender(int leftRECT);
	//왼쪽 벽 렉트그려보는 함수
	virtual void RightRectRender(int rightRECT);
	
	//상점스테이지 전용 함수(아이템 살수있는 함수)
	virtual void BuyItem();


	//포탈만드는 함수
	virtual void MakePotalCollison(string a);
	virtual void MakePotalCollison();
protected:
	int firstmap;
	bool bossBGM;


	int monsterandplayercount;
	bool istraprender;
	int hitcount;
	image* trapimg[2];
	RECT traprc[2];
	
	RECT standrc[4];
	bool istostring;
	UiManager* UiMG;
	ItemManager* ItemMG;
	image* potalimg;
	int currentpotalframe;
	RECT potal;
	int potalposX;
	int potalposY;


	int blocktype;
	//땅렉트
	_mapObj maprc[20];
	//플레이어가 왼쪽에서 오른쪽으로 부딪히는 렉트
	_mapObj rightmaprc[10];
	//플레이어가 오른쪽에서 왼쪽으로 부딪히는 렉트
	_mapObj leftmaprc[10];
	//배경
	image*	bg[3];
	//백그라운드
	image*	background;
	//맵이미지
	image* _MAP;
	

	Player* player;
	MonsterManager* MonsterMG;
};

#define DATA AllMap::GetData()