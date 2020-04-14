#include "stdafx.h"
#include "ShopStage.h"


ShopStage::ShopStage()
{
}


ShopStage::~ShopStage()
{
}

HRESULT ShopStage::init()
{
	SOUNDMANAGER->play("�������", 6);
	DATA->playerInfo.currentmapindex = 7;
	_MAP = IMAGEMANAGER->findImage("������������");
	CAMERAMANAGER->set_CameraWorldSize(1800, 1000);


	/*background = new image;
	background = IMAGEMANAGER->findImage("���2");*/
	
	maprc[0].rc = RectMake(0, 582, 1800, 100);
	
	DATA->playerInfo.locationX = 50;
	DATA->playerInfo.locationY = 400;
	AllMap::init();
	bg[0] = IMAGEMANAGER->findImage("�����ϴ�");
	bg[1] = IMAGEMANAGER->findImage("���5");
	blocktype = 0;
	potalposX = 1477;
	potalposY = 282;
	//MonsterMG->set_StoreMater({ 1271, 470 });
	for (int i = 0; i < 4; i++)
	{
		
		standrc[i] = RectMake(i* 208 +433,540 , 75, 70);
		int rand = RND->getFromIntTo(1, 10);
		//cout << rand << endl;
		ItemMG->set_Store(standrc[i].left, standrc[i].top, rand);
	}


	
	
	return S_OK;
}

void ShopStage::release()
{
}

void ShopStage::update()
{
	//AllMap::update();
	for (int i = 0; i < ItemMG->getVItem().size(); ++i)
	{
		if (ItemMG->getVItem().size() <= 0) return;

		ItemMG->getVItem()[i]->SetIsStore(true);
	}


	ItemMG->update();
	UiMG->update();
	UiMG->DrawHpBar(DATA->playerInfo.playerHP);
	UiMG->DrawCharImg(DATA->playerInfo.playertype);
	if (DATA->playerInfo.charslot.size() > 1)
	{
		UiMG->DrawSmallCharImg(DATA->playerInfo.charslot[1]);
	}


	CheakLocation();
	player->update();
	MonsterMG->update();
	MonsterAndPlayerCollion();
	BuyItem();


	MonsterAndMapCollion(1);
	PlayerAndMapCollion(1, 0, 0);
	MakePotalCollison("ĳ���ͽ�������");
}

void ShopStage::render()
{
	//background->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	for (int i = 0; i < 2; ++i)
	{

		bg[i]->loopRender(CAMERAMANAGER->getWorldDC(), &RectMake(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY), CAMERAMANAGER->get_CameraX()*i*0.5f, CAMERAMANAGER->get_CameraY());
	}
	/*GroundRectRender(1);
	LeftRectRender(0);
	RightRectRender(0);*/
	AllMap::render();
}
