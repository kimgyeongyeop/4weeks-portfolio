#include "stdafx.h"
#include "inGameScene.h"



inGameScene::inGameScene()
{
}


inGameScene::~inGameScene()
{
}

HRESULT inGameScene::init()
{
	
	_player._ATOM = new image;
	_player._ATOM = IMAGEMANAGER->addImage("아톰", "./resours/player/루피.bmp", 50, 120, true, RGB(255, 0, 255));
	_MAP = new image;
	_MAP = IMAGEMANAGER->addImage("맵", "./resours/map/testMAP.bmp", 2160, 1800, true, RGB(255, 0, 255));


	/*bg[0] = IMAGEMANAGER->addImage("tutorial_BG_0", "./resours/map/tutorial_BG_0.bmp", 2160, 1800, false, RGB(0, 0, 0));
	bg[1] = IMAGEMANAGER->addImage("tutorial_BG_1", "./resours/map/tutorial_BG_1.bmp", 2160, 1800, true, RGB(255, 0, 255));
	bg[2] = IMAGEMANAGER->addImage("tutorial_BG_2", "./resours/map/tutorial_BG_2.bmp", 2160, 1800, true, RGB(255, 0, 255));*/
	bg[0] = new image;
	bg[0] = IMAGEMANAGER->findImage("tutorial_BG_0");
	bg[1] = new image;
	bg[1] = IMAGEMANAGER->findImage("tutorial_BG_1");
	bg[2] = new image;
	bg[2] = IMAGEMANAGER->findImage("tutorial_BG_2");

	

	_player.center.x = WINSIZEX / 2;
	_player.center.y = WINSIZEY / 2;

	_player.rc = RectMakeCenter(_player.center.x , _player.center.y , _player._ATOM->getWidth(), _player._ATOM->getHeight());

	
	
	//사각형

	maprc[0].rc = RectMake(124, 321, 360, 10);
	maprc[1].rc = RectMake(1072, 324, 360, 10);
	maprc[2].rc = RectMake(610, 630 , 360, 10);
	maprc[3].rc = RectMake(128, 905, 360, 10);
	maprc[4].rc = RectMake(1085, 905, 360, 10);
	maprc[5].rc = RectMake(609, 1132, 360, 10);
	maprc[6].rc = RectMake(125, 1386, 360, 10);
	maprc[7].rc = RectMake(1076, 1358, 360, 10); //1358
	maprc[8].rc = RectMake(0, 1658, 2158, 10);
	gravitiy = 8.2f;
	jumppower = 0;
	
	states.insert(make_pair("Idle", new PlayerIdle(this)));
	states.insert(make_pair("Jump", new PlayerJump(this)));
	states.insert(make_pair("Air", new PlayerAir(this)));
	blocktype = 8;
	ChangeState("Idle");
	_player.isground = false;
	_player.isjump = false;
	
	return S_OK;
}

void inGameScene::release()
{
}

void inGameScene::update()
{
	
	
	CheakLocation();
	Gravity();


	currentState->Update();
	
	
	
	for (int i = 0; i < 9; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &maprc[i].rc, &_player.rc))
		{
			blocktype = i;
		}
		if (_player.rc.bottom< maprc[i].rc.top)
		{
			maprc[i].collion = true;
		}
		if (_player.rc.bottom > maprc[i].rc.bottom)
		{
			maprc[i].collion = false;
		}
	
	}
	
	
	RECT rc;

	
	if (IntersectRect(&rc, &maprc[blocktype].rc, &_player.rc) && maprc[blocktype].collion)
	{

		//땅일 때 (중력안줌)
		jumpcount = 0;
		_player.isground = true;
		_player.isjump = false;
		_player.center.y = maprc[blocktype].rc.top - _player._ATOM->getHeight() / 2 + 1;
		_player.rc.bottom = maprc[blocktype].rc.top;
		jumpcount = 0;
		

	}
		else
		{
			//땅이 아니다 (중력줌)
			_player.isground = false;
		}
	
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
	
		jumppower = 60.f;
		_player.isground = false;
		_player.isjump = true;
		jumpcount++;
	}


	if (_player.isjump && jumpcount<3)
	{

		_player.center.y -= jumppower;
		
		jumppower -= gravitiy;
		
		if (jumppower < 0) 
		{
			jumppower = 0;
		}

	}
	
	
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_player.center.x -= 10;
		
	}

	

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player.center.x += 10;
		
	}


	//캐릭터 렉트 계속업뎃
	_player.rc = RectMakeCenter(_player.center.x, _player.center.y, _player._ATOM->getWidth(), _player._ATOM->getHeight());
	



	

	CAMERAMANAGER->set_CameraXY(_player.center.x, _player.center.y,true);
	
}

void inGameScene::render()
{
	//IMAGEMANAGER->findImage("인게임")->render(getMemDC(), 0, 0);
	
	for (int i = 0; i < 3; ++i)
	{
		bg[i]->render(CAMERAMANAGER->getWorldDC(), 0, 0);
	}
	_MAP->render(CAMERAMANAGER->getWorldDC(), 0, 0);
	
	for (int i = 0; i < 9; ++i)
	{
		//Rectangle(CAMERAMANAGER->getWorldDC(), maprc[i].rc);
	}

	_player._ATOM->render(CAMERAMANAGER->getWorldDC(), _player.rc.left, _player.rc.top);
	//Rectangle(CAMERAMANAGER->getWorldDC(), _player.rc);

	//Rectangle(CAMERAMANAGER->getWorldDC(), _player.floorrc);

	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	

	////////
	_backBuffer->render(getHDC(), 0, 0);
}

void inGameScene::Gravity()
{
	if (_player.isground) 
	{
		jumppower = 0.f;
		gravitiy = 0.f;
	}
	if (!_player.isground)
	{
		gravitiy = 10.5f;
		_player.center.y += gravitiy;
	}
	
}

void inGameScene::CheakLocation()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{


		POINT pos;
		::GetCursorPos(&pos);  //마우스 포인터 좌표 가져와줌
		::ScreenToClient(_hWnd, &pos); // api창안에서만 가져올수있게 보정
		cout << pos.x + CAMERAMANAGER->get_CameraX() << "," << pos.y + CAMERAMANAGER->get_CameraY() << endl;

	}

}


void inGameScene::ChangeState(string key)
{
	PlayerBase* state = states[key];
	state->Enter();
	currentState = state;
}


void PlayerIdle::Enter()
{
	
	
}

void PlayerIdle::Update()
{
	

	
}

void PlayerJump::Enter()
{

	/*me->_player.isground = false;;
	me->jumppower = 5;*/
}

void PlayerJump::Update()
{
	/*me->_player.center.y -= me->jumppower;
	me->jumppower -= me->gravitiy;

		RECT rc;
		for (int i = 0; i < 9; i++)
		{
			if (IntersectRect(&rc, &me->maprc[i], &me->_player.rc))
			{
				me->blocktype = i;
				me->ChangeState("Idle");
			}
			
		}*/
		
}


void PlayerAir::Enter()
{

	//me->gravitiy = 1.8;
}

void PlayerAir::Update()
{
	
	//me->_player.center.y += me->gravitiy;
}