#pragma once
#include "gameNode.h"
#include "tileNode.h"

class tankMap : public gameNode
{
private:
	tagTile	_tiles[TILEX * TILEY];
	DWORD _attribute[TILEX * TILEY];	//*Ÿ�ϼӼ��ο�*
	
	//�ѸǶ��� ������...
	int _pos[2];

public:
	tankMap();
	~tankMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void load();

	tagTile* getTile() { return _tiles; }

	//2. �Ӽ��ο����� �ܺο��� �����ϰ� �����ڰ� �ʿ��ϴ�
	DWORD* getAttribute() { return _attribute; }

	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }

};

