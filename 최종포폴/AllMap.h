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
	//�ʿ� ��ǥ �˾ƿ��� �Լ�
	virtual void CheakLocation();
	//�÷��̾�� �� �浹�Լ�
	virtual void PlayerAndMapCollion(int groundRECT, int leftRECT, int rightRECT);
	//���Ͷ� �� �浹�Լ�
	virtual void MonsterAndMapCollion(int groundRECT);
	//���Ͷ� �÷��̾� �浹
	virtual void MonsterAndPlayerCollion();
	//�÷��̾�� ������ �浹 
	virtual void PlayerAndItemCollion();
	//�� ��Ʈ �׷������Լ�
	virtual void GroundRectRender(int groundRECT);
	//������ �� ��Ʈ�׷������Լ�
	virtual void LeftRectRender(int leftRECT);
	//���� �� ��Ʈ�׷����� �Լ�
	virtual void RightRectRender(int rightRECT);
	
	//������������ ���� �Լ�(������ ����ִ� �Լ�)
	virtual void BuyItem();


	//��Ż����� �Լ�
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
	//����Ʈ
	_mapObj maprc[20];
	//�÷��̾ ���ʿ��� ���������� �ε����� ��Ʈ
	_mapObj rightmaprc[10];
	//�÷��̾ �����ʿ��� �������� �ε����� ��Ʈ
	_mapObj leftmaprc[10];
	//���
	image*	bg[3];
	//��׶���
	image*	background;
	//���̹���
	image* _MAP;
	

	Player* player;
	MonsterManager* MonsterMG;
};

#define DATA AllMap::GetData()