#include "stdafx.h"
#include "Item.h"


Item::Item()
{
}


Item::~Item()
{
}

HRESULT Item::init(float posx, float posy, string img)
{
	itemposX = posx;
	itemposY = posy;
	itemimg = IMAGEMANAGER->findImage(img);
	currentFrameX = 0;
	rc = RectMake(posx, posy, itemimg->getFrameWidth(), itemimg->getFrameHeight());
	ismove = true;
	isstore = false;
	moneyimg = IMAGEMANAGER->findImage("������");
	return S_OK;
}

void Item::release()
{
}

void Item::update()
{
	frame(); 
	
}

void Item::render()
{
	itemimg->frameRender(CAMERAMANAGER->getWorldDC(), rc.left, rc.top, currentFrameX, 0);
	PriceRender();
}

void Item::Move()
{
	

}

void Item::frame()
{
	count++;
	if (count % 10 == 0)
	{
		currentFrameX++;
		count = 0;
	}
	if (currentFrameX >= itemimg->getMaxFrameX()) {

		currentFrameX = 0;

	}
}

void Item::PriceRender()
{
	if (isstore)
	{
		HFONT myFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "�޸鱼��");
		HFONT oldFont = (HFONT)SelectObject(CAMERAMANAGER->getWorldDC(), myFont);
		//SetBkMode(CAMERAMANAGER->getWorldDC(), TRANSPARENT);
		if (DATA->playerInfo.playerMoney < price)
		{
			SetBkColor(CAMERAMANAGER->getWorldDC(), RGB(255, 0, 0));
		}
		else if (DATA->playerInfo.playerMoney >= price)
		{
			SetBkColor(CAMERAMANAGER->getWorldDC(), RGB(255, 255, 255));
		}
		char str[10];
		sprintf_s(str, "%d", price);
		TextOut(CAMERAMANAGER->getWorldDC(), rc.left, rc.bottom+50, str, strlen(str));
		moneyimg->render(CAMERAMANAGER->getWorldDC(), rc.left - moneyimg->getWidth(), rc.bottom + 50);

		//Rectangle(CAMERAMANAGER->getWorldDC(), rc);
		SetBkColor(CAMERAMANAGER->getWorldDC(), RGB(255, 255, 255));

		POINT worldmousepos;
		worldmousepos.x = _ptMouse.x + CAMERAMANAGER->get_CameraX();
		worldmousepos.y = _ptMouse.y + CAMERAMANAGER->get_CameraY();


		

		if (PtInRect(&rc, worldmousepos))
		{
			

			char str1[50];
			

			switch (itemindex)
			{
			case 1: 
				sprintf_s(str1, "%s", "ü�� 30 �÷���");
				TextOut(CAMERAMANAGER->getWorldDC(), rc.left-100, rc.top - 100, str1, strlen(str1));
				break;
			case 2:
				sprintf_s(str1, "%s", "ü�� 60 �÷���");
				TextOut(CAMERAMANAGER->getWorldDC(), rc.left - 100, rc.top - 100, str1, strlen(str1));
				break;
			case 7:
				sprintf_s(str1, "%s", "���� 5 �÷���");
				TextOut(CAMERAMANAGER->getWorldDC(), rc.left - 100, rc.top - 100, str1, strlen(str1));
				break;
			case 8:
				sprintf_s(str1, "%s", "���� 10 �÷���");
				TextOut(CAMERAMANAGER->getWorldDC(), rc.left - 100, rc.top - 100, str1, strlen(str1));
				break;
			case 9:
				sprintf_s(str1, "%s", "���ǵ� 3 �÷���");
				TextOut(CAMERAMANAGER->getWorldDC(), rc.left - 100, rc.top - 100, str1, strlen(str1));
				break;
			case 10:
				sprintf_s(str1, "%s", "���ݷ� 5 �÷���");
				TextOut(CAMERAMANAGER->getWorldDC(), rc.left - 100, rc.top - 100, str1, strlen(str1));
				break;
			case 11:
				sprintf_s(str1, "%s", "���ݻ�Ÿ� 10 �÷���");
				TextOut(CAMERAMANAGER->getWorldDC(), rc.left - 100, rc.top - 100, str1, strlen(str1));
				break;
			case 12:
				sprintf_s(str1, "%s", "ũ��Ƽ��Ȯ�� 10% �÷���");
				TextOut(CAMERAMANAGER->getWorldDC(), rc.left - 100, rc.top - 100, str1, strlen(str1));
				break;
		
			}
			






		}


		SelectObject(CAMERAMANAGER->getWorldDC(), oldFont);
		DeleteObject(myFont);

		
		


	}
}
