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
	virtual void Move(); // ������..
	virtual void frame();
	virtual void PriceRender();
	
	//���ͼ���
	virtual void SetIsMove(bool set) {ismove = set;}
	virtual RECT GetItemRc() { return rc; }
	virtual void SetPositemposY(int a) { itemposY = a - itemimg->getFrameHeight(); }
	virtual int GetItemIndex() { return itemindex; }
	virtual void SetIsStore(bool is) { isstore = is; }
	virtual int GetItemPrice() {return price;}

protected:
	//�������ε���
	int itemindex;
	//������϶� ���͵�
	int price;
	bool isstore;
	//��������ġ
	float itemposX;
	float itemposY;
	//����
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

