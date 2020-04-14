#pragma once
#include "gameNode.h"
#include "tileNode.h"

class tankMap : public gameNode
{
private:
	tagTile	_tiles[TILEX * TILEY];
	DWORD _attribute[TILEX * TILEY];	//*타일속성부여*
	
	//팩맨때는 쓸꺼임...
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

	//2. 속성부여값을 외부에서 접근하게 접근자가 필요하다
	DWORD* getAttribute() { return _attribute; }

	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }

};

