#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(string name, float x, float y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	string front, back;   // sting 자료형은 바로 초기화하면 위험!!!
	front = name + "frontBar";
	back = name + "backBar";


	_progressBarTop = IMAGEMANAGER->findImage(front);
	_progressBarBottom = IMAGEMANAGER->findImage(back);

	//뒤에 깔리는 게이지의 가로크기를 기준으로 삼는다
	_width = _progressBarBottom->getWidth();
	//cout << _progressBarBottom->getWidth() << endl;

	return S_OK;

}

void progressBar::release()
{
}

void progressBar::update()
{
	//일단은 중점으로 해둠
	_rcProgress = RectMakeCenter(_x, _y, _progressBarTop->getWidth(), _progressBarBottom->getHeight());

}

void progressBar::render(HDC a)
{
	/*IMAGEMANAGER->render("backBar", CAMERAMANAGER->getWorldDC(),
		_rcProgress.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());
	
	IMAGEMANAGER->render("frontBar", CAMERAMANAGER->getWorldDC(),
		_rcProgress.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_width, _progressBarBottom->getHeight());
*/
	_progressBarBottom->render(a,
		_rcProgress.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	_progressBarTop->render(a,
		_rcProgress.left+ _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_width, _progressBarBottom->getHeight());
	//cout << _width << "," << _progressBarBottom->getHeight() << endl;

}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();

}
