#pragma once
#include "gameNode.h"
#include "progressBar.h"
class UiManager : public gameNode
{
public:
	UiManager();
	~UiManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void DrawHpBar(int HP);
	virtual void DrawCharImg(int a);
	virtual void DrawSmallCharImg(int b);
	virtual void DrawMoney(int don);
	

private :
	image* minimap;
	image* itemimg;

	bool minimapswitch;
	image* playerinfoimg;
	RECT playerinforc;
	bool isplayerinfoimg;
	image* skillimg;
	image* charimg;
	image* smallcharimg;
	image* skillslot;
	image* Moneyimg;
	image* Number[10];
	//프로그래스바
	progressBar* HpBar;
	progressBar* skill1Bar;
	progressBar* skill2Bar;
	progressBar* skill3Bar;
	progressBar* skill4Bar;
	float playercurrentHP, playermaxHP, skillcurrent1, skillcurrent2, skillcurrent3, skillmax;
	RECT miniplayer;
	//progressBar* skillcooltime;
};

