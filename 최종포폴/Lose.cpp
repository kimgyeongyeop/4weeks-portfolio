#include "stdafx.h"
#include "Lose.h"


Lose::Lose()
{
}


Lose::~Lose()
{
}

HRESULT Lose::init()
{
	_background = IMAGEMANAGER->findImage("�й��");

	min = DATA->playerInfo.playtime / 60;
	hour = min / 60;
	sec = DATA->playerInfo.playtime % 60;
	min = min % 60;
	return S_OK;
}

void Lose::release()
{
}

void Lose::update()
{
}

void Lose::render()
{
	_background->render(getMemDC(), 0, 0);


	HFONT myFont = CreateFont(100, 0, 0, 0, 500, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "�޸鱼��");
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 0, 0));
	char str[100];







	sprintf_s(str, "%d : %d : %d", hour, min, sec);
	TextOut(getMemDC(), 900, 250, str, strlen(str));


	sprintf_s(str, "%d", DATA->playerInfo.playerMoney);
	TextOut(getMemDC(), 900, 450, str, strlen(str));

	sprintf_s(str, "%d", DATA->playerInfo.Killnum);
	TextOut(getMemDC(), 900, 650, str, strlen(str));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
}
