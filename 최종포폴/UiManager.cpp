#include "stdafx.h"
#include "UiManager.h"


UiManager::UiManager()
{
}


UiManager::~UiManager()
{
}

HRESULT UiManager::init()
{
	minimap = IMAGEMANAGER->findImage("미니맵1");
	itemimg = IMAGEMANAGER->findImage("구슬");

	playerinfoimg= IMAGEMANAGER->findImage("플레이어정보창");
	charimg = IMAGEMANAGER->findImage("오타쿠이미지");
	smallcharimg = IMAGEMANAGER->findImage("초기작은이미지");
	skillslot = IMAGEMANAGER->findImage("skillslot");
	playermaxHP = 200; 
	skillcurrent1 = 0;
	skillcurrent2 = 0;
	skillcurrent3 = 0;
	skillmax = 60;
	//플레이어 목숨
	IMAGEMANAGER->addImage("playerHPfrontBar", "hpBarTop.bmp", playermaxHP, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerHPbackBar", "hpBarBottom.bmp", playermaxHP, 20, true, RGB(255, 0, 255));
	HpBar = new progressBar;
	HpBar->init("playerHP", 100, WINSIZEY - 100, playermaxHP, 20);

	//스킬1 쿨타임
	IMAGEMANAGER->addImage("skill1frontBar", "hpBarTop.bmp", skillmax, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("skill1backBar", "hpBarBottom.bmp", skillmax, 10, true, RGB(255, 0, 255));
	skill1Bar = new progressBar;
	skill1Bar->init("skill1", 100, WINSIZEY - 130, 10, 10);

	IMAGEMANAGER->addImage("skill2frontBar", "hpBarTop.bmp", skillmax, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("skill2backBar", "hpBarBottom.bmp", skillmax, 10, true, RGB(255, 0, 255));
	skill2Bar = new progressBar;
	skill2Bar->init("skill2", 100 +75, WINSIZEY - 130, 10, 10);

	IMAGEMANAGER->addImage("skill3frontBar", "hpBarTop.bmp", skillmax, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("skill3backBar", "hpBarBottom.bmp", skillmax, 10, true, RGB(255, 0, 255));
	skill3Bar = new progressBar;
	skill3Bar->init("skill3", 100 + 75*2, WINSIZEY - 130, 10, 10);


	IMAGEMANAGER->addImage("skill4frontBar", "hpBarTop.bmp", skillmax, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("skill4backBar", "hpBarBottom.bmp", skillmax, 10, true, RGB(255, 0, 255));
	skill4Bar = new progressBar;
	skill4Bar->init("skill4", 100 + 75 * 3-35, WINSIZEY - 130, 10, 10);


	skillmax = 100;

	Moneyimg = IMAGEMANAGER->findImage("돈모양");

	for (int i = 0; i < 10; i++)
	{
		char num[10];
		sprintf_s(num, "%d", i);
		Number[i]= IMAGEMANAGER->findImage(num);
	}

	minimapswitch = true;
	isplayerinfoimg = false;
	return S_OK;
}

void UiManager::release()
{
}

void UiManager::update()
{
	HpBar->update();



	if (DATA->playerInfo.playertype >= 1 && DATA->playerInfo.playertype <= 3)
	{
		skill1Bar->update();
		skill2Bar->update();
		skill3Bar->update();

		

		skill1Bar->setGauge(DATA->playerInfo.skill1cooltime, skillmax);
		skill2Bar->setGauge(DATA->playerInfo.skill2cooltime, skillmax);
		skill3Bar->setGauge(DATA->playerInfo.skill3cooltime, skillmax);

		DATA->playerInfo.skill1cooltime += 0.5;
		DATA->playerInfo.skill2cooltime += 0.5;
		DATA->playerInfo.skill3cooltime += 0.5;
	}


	if (DATA->playerInfo.isitem)
	{
		skill4Bar->setGauge(DATA->playerInfo.skill4cooltime, skillmax);
		DATA->playerInfo.skill4cooltime += 0.5;
	}


	if (DATA->playerInfo.skill1cooltime >= skillmax)
	{
		DATA->playerInfo.skill1cooltime = skillmax;
	}
	if (DATA->playerInfo.skill2cooltime >= skillmax)
	{
		DATA->playerInfo.skill2cooltime = skillmax;
	}
	if (DATA->playerInfo.skill3cooltime >= skillmax)
	{
		DATA->playerInfo.skill3cooltime = skillmax;
	}
	if (DATA->playerInfo.skill4cooltime >= skillmax)
	{
		DATA->playerInfo.skill4cooltime = skillmax;
	}

	
	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		if(minimapswitch)
		minimapswitch = false;

		else if (!minimapswitch)
			minimapswitch = true;
	}

	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		if (isplayerinfoimg)
			isplayerinfoimg = false;

		else if (!isplayerinfoimg)
			isplayerinfoimg = true;
	}

	playerinforc = RectMake(200, 300, playerinfoimg->getWidth(), playerinfoimg->getHeight());

	miniplayer = RectMake(WINSIZEX - 500 + DATA->playerInfo.currentplayerPos.x/8, WINSIZEY - 300 + DATA->playerInfo.currentplayerPos.y/8, 10, 10);


	switch (DATA->playerInfo.currentmapindex )
	{
	case 1: 
		minimap = IMAGEMANAGER->findImage("미니맵1");
		break;
	case 2:
		minimap = IMAGEMANAGER->findImage("미니맵2");
		break;
	case 3:
		minimap = IMAGEMANAGER->findImage("미니맵3");
		break;
	case 4:
		minimap = IMAGEMANAGER->findImage("미니맵4");
		break;
	case 5:
		minimap = IMAGEMANAGER->findImage("미니맵5");
		break;
	case 6:
		minimap = IMAGEMANAGER->findImage("미니맵6");
		break;
	case 7:
		minimap = IMAGEMANAGER->findImage("미니맵7");
		break;
	case 8:
		minimap = IMAGEMANAGER->findImage("미니맵8");
		break;
	case 9:
		minimap = IMAGEMANAGER->findImage("미니맵9");
		break;
	
		
	}

}

void UiManager::render()
{
	HpBar->render(getMemDC());
	//if(charimg)
	charimg->render(getMemDC(), 0, WINSIZEY - 120);
	smallcharimg->render(getMemDC(), 100, WINSIZEY - 70);
	//if(skillslot)
		skillslot->render(getMemDC(), 100, WINSIZEY - 200);

		if (DATA->playerInfo.playertype >= 1 && DATA->playerInfo.playertype <= 3)
		{

			skill1Bar->render(getMemDC());
			skill2Bar->render(getMemDC());
			skill3Bar->render(getMemDC());
		}

		Moneyimg->render(getMemDC(), WINSIZEX - 200, 20);

		DrawMoney(DATA->playerInfo.playerMoney);

		if (minimapswitch)
		{
			minimap->render(getMemDC(), WINSIZEX - 500, WINSIZEY - 300);

			HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			Rectangle(getMemDC(), miniplayer);
			SelectObject(getMemDC(), oldBrush);
			DeleteObject(brush);
			//StretchBlt(getMemDC(), WINSIZEX - 500, WINSIZEY - 300, 400, 240, CAMERAMANAGER->getWorldDC(), 0, 0, CAMERAMANAGER->get_MaxWorldSizeX(), CAMERAMANAGER->get_MaxWorldSizeY(), SRCCOPY);
		}
		if (isplayerinfoimg)
		{
			playerinfoimg->render(getMemDC(), playerinforc.left , playerinforc.top);

			//정보쓰기
			HFONT myFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "휴면굴림");
			HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
			SetTextColor(getMemDC(), RGB(0, 0, 0));
			SetBkMode(getMemDC(), TRANSPARENT);

			char str[30];
			
			//cout << DATA->playerInfo.playerPOWER << "," << DATA->playerInfo.playerAMOR << ',' << DATA->playerInfo.playerSPEED << endl;
			sprintf_s(str, "%d", DATA->playerInfo.playerPOWER);
			TextOut(getMemDC(), playerinforc.left+100, playerinforc.top+45, str, strlen(str));
			sprintf_s(str, "%d", DATA->playerInfo.playerAMOR);
			TextOut(getMemDC(), playerinforc.left + 100, playerinforc.top+85, str, strlen(str));
			sprintf_s(str, "%d", DATA->playerInfo.playerSPEED);
			TextOut(getMemDC(), playerinforc.left + 100, playerinforc.top+125, str, strlen(str));
			sprintf_s(str, "%d", DATA->playerInfo.playerATKRANGE);
			TextOut(getMemDC(), playerinforc.left + 100, playerinforc.top + 165, str, strlen(str));
			sprintf_s(str, "%d", DATA->playerInfo.playerCRITICAL);
			TextOut(getMemDC(), playerinforc.left + 100, playerinforc.top + 205, str, strlen(str));
			/*sprintf_s(str, "%d", DATA->playerInfo.playerPOWER);
			TextOut(getMemDC(), playerinforc.left, playerinforc.top, str, strlen(str));*/

			SelectObject(getMemDC(), oldFont);
			DeleteObject(myFont);



		}

		if (DATA->playerInfo.isitem)
		{
			skill4Bar->render(getMemDC());
			itemimg->render(getMemDC(), 323, WINSIZEY - 190);
		}



	//150, WINSIZEY - 100
}

void UiManager::DrawHpBar(int CurrentHP)
{
	if (CurrentHP > 200)
	{
		DATA->playerInfo.playerHP = 200;
	}
	HpBar->setGauge(CurrentHP, playermaxHP);
}

void UiManager::DrawCharImg(int a)
{
	switch (a)
	{
	case 0:

		skillslot = IMAGEMANAGER->findImage("skillslot");
		charimg = IMAGEMANAGER->findImage("오타쿠이미지");
		//skill1Bar = nullptr;
		//charimg = nullptr;
		//skillimg = nullptr;
		break;
	case 1:
		skillslot = IMAGEMANAGER->findImage("나루토skillslot");
		charimg = IMAGEMANAGER->findImage("나루토이미지");
		break;
	case 2:
		skillslot = IMAGEMANAGER->findImage("루피skillslot");
		charimg = IMAGEMANAGER->findImage("루피이미지");
		break;
	case 3:
		skillslot = IMAGEMANAGER->findImage("손오공skillslot");
		charimg = IMAGEMANAGER->findImage("손오공이미지");
		break;
	
	}

}

void UiManager::DrawSmallCharImg(int b)
{
	switch (b)
	{
	case 0:


		smallcharimg = IMAGEMANAGER->findImage("오타쿠작은이미지");

		break;
	case 1:
		smallcharimg = IMAGEMANAGER->findImage("나루토작은이미지");
		break;
	case 2:
		smallcharimg = IMAGEMANAGER->findImage("루피작은이미지");
		break;
	case 3:
		smallcharimg = IMAGEMANAGER->findImage("손오공작은이미지");
		break;

	}
}






void UiManager::DrawMoney(int don)
{
	int heightrange=30;//위에서부터 세로길이;

	if (don >= 1000)
	{
		int a;
		int b;
		int c;
		int d;
		a = don / 1000;
		b = (don % 1000) / 100;
		c = (don % 1000) % 100 /10;
		d = (don % 1000) % 100 % 10;
		Number[a]->render(getMemDC(), WINSIZEX - 120, heightrange);
		Number[b]->render(getMemDC(), WINSIZEX - 100, heightrange);
		Number[c]->render(getMemDC(), WINSIZEX - 80, heightrange);
		Number[d]->render(getMemDC(), WINSIZEX - 60, heightrange);

	}
	else if (don >= 100) {
		int a;
		int b;
		int c;
		a = don / 100;
		b = (don % 100) / 10;
		c = (don % 100)  % 10;
		Number[a]->render(getMemDC(), WINSIZEX - 100, heightrange);
		Number[b]->render(getMemDC(), WINSIZEX - 80, heightrange);
		Number[c]->render(getMemDC(), WINSIZEX - 60, heightrange);
	}
	else if (don >= 10) {
		int a;
		int b;
		a = don / 10;
		b = don % 10;
		Number[a]->render(getMemDC(), WINSIZEX - 80, heightrange);
		Number[b]->render(getMemDC(), WINSIZEX - 60, heightrange);
	}
	else if (don < 10) {

		Number[don]->render(getMemDC(), WINSIZEX -60, heightrange);
	}


}


