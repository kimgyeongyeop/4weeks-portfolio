#include "stdafx.h"
#include "ItemManager.h"


ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

HRESULT ItemManager::init()
{
	return S_OK;
}

void ItemManager::release()
{
}

void ItemManager::update()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->update();
	}

}

void ItemManager::render()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->render();
	}
	//CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
}

void ItemManager::RemoveItem(int arr)
{
	_vItem.erase(_vItem.begin() + arr);

}

void ItemManager::set_Hp(float posx,float posy)
{
	HpItem* item1 = new HpItem;
	item1->init(posx, posy, "작은포션");
	_vItem.push_back(item1);
}

void ItemManager::set_BigHp(float posx, float posy)
{
	BigHpItem* item2 = new BigHpItem;
	item2->init(posx, posy, "큰포션");
	_vItem.push_back(item2);
}

void ItemManager::set_Money(float posx, float posy)
{
	MoneyItem* item3 = new MoneyItem;
	item3->init(posx, posy, "돈");
	_vItem.push_back(item3);
}

void ItemManager::set_NarutoBook(float posx, float posy)
{
	NarutoBook* item4 = new NarutoBook;
	item4->init(posx, posy, "나루토책");
	_vItem.push_back(item4);
}

void ItemManager::set_LuffyBook(float posx, float posy)
{
	LuffyBook* item5 = new LuffyBook;
	item5->init(posx, posy, "원피스책");
	_vItem.push_back(item5);
}

void ItemManager::set_SonoGongBook(float posx, float posy)
{
	SonoGongBook* item6 = new SonoGongBook;
	item6->init(posx, posy, "드래곤볼책");
	_vItem.push_back(item6);
}



void ItemManager::set_CharBook(float posx, float posy, int rand)
{
	if (rand == 1)
	{
		NarutoBook* item4 = new NarutoBook;
		item4->init(posx, posy, "나루토책");
		_vItem.push_back(item4);
	}
	else if (rand == 2)
	{
		LuffyBook* item5 = new LuffyBook;
		item5->init(posx, posy, "원피스책");
		_vItem.push_back(item5);

	}
	else if (rand == 3)
	{
		SonoGongBook* item6 = new SonoGongBook;
		item6->init(posx, posy, "드래곤볼책");
		_vItem.push_back(item6);

	}

}

void ItemManager::set_Store(float posx, float posy, int rand)
{
	if (rand == 1)
	{
		HpItem* item1 = new HpItem;
		item1->init(posx, posy, "작은포션");
		_vItem.push_back(item1);
	}
	else if (rand == 2)
	{
		BigHpItem* item2 = new BigHpItem;
		item2->init(posx, posy, "큰포션");
		_vItem.push_back(item2);
	}

	else if (rand == 3)
	{
		HeadPiece* item7 = new HeadPiece;
		item7->init(posx, posy, "모자");
		_vItem.push_back(item7);
	}

	else if (rand == 4)
	{
		SteelArmor* item8 = new SteelArmor;
		item8->init(posx, posy, "방어구");
		_vItem.push_back(item8);
	}

	else if (rand == 5)
	{
		SpeedShoes* item9 = new SpeedShoes;
		item9->init(posx, posy, "신발");
		_vItem.push_back(item9);
	}
	else if (rand == 6)
	{
		PowerSword* item10 = new PowerSword;
		item10->init(posx, posy, "공격력검");
		_vItem.push_back(item10);
	}
	else if (rand == 7)
	{
		RangeSword* item11 = new RangeSword;
		item11->init(posx, posy, "사거리검");
		_vItem.push_back(item11);
	}
	
	else if (rand == 8)
	{
		Gloves* item12 = new Gloves;
		item12->init(posx, posy, "장갑");
		_vItem.push_back(item12);
	}
	else if (rand == 9)
	{
		Marble* item13 = new Marble;
		item13->init(posx, posy, "구슬");
		_vItem.push_back(item13);
	}

}

void ItemManager::set_FinalBook(float posx, float posy)
{
	FinalItem* item14 = new FinalItem;
	item14->init(posx, posy, "마지막책");
	_vItem.push_back(item14);

}
