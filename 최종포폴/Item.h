#pragma once
#include "gameNode.h"
#define PI 3.14
#define DO PI/180
class Item :public gameNode
{
public:
	Item();
	~Item();

	virtual HRESULT init(float posx, float posy, string img);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void Move(); // 움직임..
	virtual void frame();
	virtual void PriceRender();
	
	//겟터셋터
	virtual void SetIsMove(bool set) {ismove = set;}
	virtual RECT GetItemRc() { return rc; }
	virtual void SetPositemposY(int a) { itemposY = a - itemimg->getFrameHeight(); }
	virtual int GetItemIndex() { return itemindex; }
	virtual void SetIsStore(bool is) { isstore = is; }
	virtual int GetItemPrice() {return price;}

protected:
	//아이템인덱스
	int itemindex;
	//스토어일때 쓸것들
	int price;
	bool isstore;
	//아이템위치
	float itemposX;
	float itemposY;
	//각도
	float angle;
	image* moneyimg;
	image* itemimg;
	RECT rc;
	int count;
	int currentFrameX;
	bool ismove;


	bool choiceAngle;
	float gravity;
	float Xspeed;
	float Yspeed;
	float firstPosY;
	
};

