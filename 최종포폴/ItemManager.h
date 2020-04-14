#pragma once
#include"gameNode.h"
#include <vector>
//아이템 인덱스 순서대로 
#include"HpItem.h" //1
#include"BigHpItem.h" //2
#include"MoneyItem.h" //3
#include"NarutoBook.h" //4
#include"LuffyBook.h" // 5
#include"SonoGongBook.h"// 6
#include"HeadPiece.h"// 7
#include"SteelArmor.h"// 8
#include"SpeedShoes.h"// 9
#include"PowerSword.h"// 10
#include"RangeSword.h"// 11
#include"Gloves.h" //12
#include "Marble.h"//13
#include "FinalItem.h"//14

class ItemManager : public gameNode
{
public:
	ItemManager();
	~ItemManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void RemoveItem(int arr);
	void set_Hp(float posx, float posy);
	void set_BigHp(float posx, float posy);
	void set_Money(float posx, float posy);
	void set_NarutoBook(float posx, float posy);
	void set_LuffyBook(float posx, float posy);
	void set_SonoGongBook(float posx, float posy);
	void set_CharBook(float posx, float posy, int rand);
	void set_Store(float posx, float posy, int rand);
	void set_FinalBook(float posx, float posy);

	vector<Item*> getVItem() { return _vItem; }
	vector<Item*>::iterator getViItem() { return  _viItem; }

private:
	vector<Item*>           _vItem;
	vector<Item*>::iterator _viItem;
};

