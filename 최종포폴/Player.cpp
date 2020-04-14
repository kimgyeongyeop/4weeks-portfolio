#include "stdafx.h"
#include "Player.h"
#include "MonsterManager.h"

Player::Player()
{
}


Player::~Player()
{
}

HRESULT Player::init()
{
	sumgravity = 0.1f;
     hitframecount = 0;
	 hitcurrentFrameX =0;
     hitcurrentFrameY =0;

	_itemMG = new ItemManager;
	_itemMG->init();
	narutoBullet = new Bullet;
	narutoBullet->init("수리검",30,1000);

	itemBullet = new Bullet;
	itemBullet->init("아이템총알", 50, 1200);
	//skillcount = 0;
	Onegicount = 0;
	
	OnegiframeX = 0;
	isOnegi = false;
	
	_player.skillindex = 0;
	ishit = false;
	_player.isCommand = false;
	energysizex = 0;
	errorX=errorY = 0;
	currentFrameX = 0;
	currentFrameY = 0;
	atktime = 0;
	//■■■■■■■■■■■■■■■■■■■■■■■■■기본캐릭터 애니메이션■■■■■■■■■■■■■■■■■■■■■■■■
	isskill = false;
	isrightenergy = false;
	isleftenergy = false;
	basicplayer = IMAGEMANAGER->findImage("기본캐릭터");
	frontenergy = IMAGEMANAGER->findImage("에너지파오른쪽");
	backenergy = IMAGEMANAGER->findImage("에너지파왼쪽");
	//playertype = 0;
	anicount = 0;
	Onegi = IMAGEMANAGER->findImage("원기옥");
	Dragon = IMAGEMANAGER->findImage("신룡1");
	Scnt = 0;
	FrameX = -1;
	Fexit = true;
	energyrange = 0;
	int RIGHTIDLE1[] = { 0,1,2,3,4 };
	
	BasicPlayerAni = new animation;
	BasicPlayerAni-> init(basicplayer->getWidth(), basicplayer->getHeight(),
		basicplayer->getFrameWidth(), basicplayer->getFrameHeight());
	BasicPlayerAni-> setPlayFrame(RIGHTIDLE1, 4, true);
	BasicPlayerAni-> setFPS(1);

	
	
	
	EFFECTMANAGER->addEffect("연막이펙트", "./resours/effect/연막이펙트.bmp", 356, 109, 89, 109, 1.f, 0.1f, 5); //0.5
	EFFECTMANAGER->addEffect("빛이펙트", "./resours/effect/빛이펙트.bmp", 312, 90, 78, 90, 1.f, 0.1f, 5);  // 0.5
	EFFECTMANAGER->addEffect("파란빛이펙트", "./resours/effect/파란빛이펙트.bmp", 480, 117, 120, 117, 1.f, 0.1f, 5);

	

	EFFECTMANAGER->addEffect("기본피격", "./resours/effect/기본피격.bmp", 450, 110, 112, 110, 1.f, 0.19f, 200); //0.19
	EFFECTMANAGER->addEffect("번개", "./resours/effect/번개이펙트.bmp", 400, 236, 66, 236, 1.f, 0.19f, 80); //0.19
	EFFECTMANAGER->addEffect("마구패", "./resours/effect/나선환이펙트.bmp", 700, 121, 87, 121, 1.f, 0.19f, 80); //0.19
	EFFECTMANAGER->addEffect("태풍", "./resours/effect/태풍이펙트.bmp", 500, 129, 100, 129, 1.f, 0.19f, 80); //0.19
	EFFECTMANAGER->addEffect("에너지파맞을때", "./resours/effect/에너지파맞을때.bmp", 1000, 87, 91, 87, 1.f, 0.3f, 80); //0.19
	EFFECTMANAGER->addEffect("치명타", "./resours/effect/치명타.bmp", 2051, 150, 256, 150, 1.f, 0.3f, 5);
	EFFECTMANAGER->addEffect("나루토스킬이펙트오른쪽", "./resours/effect/나루토스킬이펙트오른쪽.bmp", 456, 134, 114, 134, 1.f, 0.1f, 5);
	EFFECTMANAGER->addEffect("나루토스킬이펙트왼쪽", "./resours/effect/나루토스킬이펙트왼쪽.bmp", 456, 134, 114, 134, 1.f, 0.1f, 5);
	//EFFECTMANAGER->addEffect("수리검이펙트", "./resours/effect/수리검이펙트.bmp", 2600, 100, 186, 100, 1.f, 0.1f, 5);
	//플레이어 첫좌표초기화 
	//DATA->playerInfo
	_player.center.x = DATA->playerInfo.locationX;
	_player.center.y = DATA->playerInfo.locationY;
	//플레이어 렉트초기화
	_player.rc = RectMakeCenter(_player.center.x, _player.center.y, 50, 120);



	_player.isground = false;
	_player.isjump = false;
	PS = PLAYER_RIGHT_IDLE;
	PC = BASIC;
	/*currentState = nullptr;

	states.insert(make_pair("naruto", new PlayerNaruto(this)));
	states.insert(make_pair("luffy", new PlayerLuffy(this)));
	
	
	ChangeState("naruto");*/
	_player.speed = 6;
	playertype = 0;

	hitimg = IMAGEMANAGER->findImage("나루토피격");
	issethit = false;

	

	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	DATA->playerInfo.playerHP = 200;

	DATA->playerInfo.currentplayerPos = { (LONG)_player.center.x ,(LONG)_player.center.y };

	if(DATA->playerInfo.playerHP<=0)
		SCENEMANAGER->changeScene("패배씬");


	//DATA->playerInfo.playerHP = 1000;

	EFFECTMANAGER->update();
	_itemMG->update();
	OneGi();
	EndSkillRect();
	narutoBullet->update();
	itemBullet->update();
	DATA->playerInfo.playertype = DATA->playerInfo.charslot[0];



	/*if(DATA->playerInfo.charslot.size()>0)
	DATA->playerInfo.playertype = DATA->playerInfo.charslot[0];*/

	if (!Fexit)
	{
		SetDragon();
	}

	
	
	
	
	//if (currentState) // 값이 있으면 업데이트 시켜라.
	//	currentState->Update();
	SkillFrame();
	PlayerTypeChange();

	

	
	BasicPlayerAni->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	//항상중력주기
	Gravity();
	//플레이어 컨트롤
	Player_Controll();
	//플레이어 상태(이미지)
	Player_State();
	//월드맵 크기만큼 충돌
	WindowMapCollison();
	//플레이어랑 몬스터충돌
	MonsterCollison();
	//플레이어랑 아이템충돌
	PlayerAndItemCollison();
	
	

	
	//플레이어 충돌렉트 계속해서 업뎃
	_player.rc = RectMakeCenter(_player.center.x, _player.center.y, 50, 100);
	//카메라를 플레이어 기준으로 둔다.
	CAMERAMANAGER->set_CameraXY(_player.center.x, _player.center.y);
	//(POINT{ (int)_player.center.x, (int)_player.center.y })
	
}

void Player::render()
{
	

	if (!Fexit) {
		CAMERAMANAGER->Camera_WorldDC_Shake();
		Dragon->frameRender(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), FrameX, 0);
	}
	EFFECTMANAGER->render();




	

		if (!isskill)
		{
			if (!issethit)
			{

				basicplayer->aniRender(CAMERAMANAGER->getWorldDC(), _player.rc.left - 30, _player.rc.top - 20, BasicPlayerAni);
			}

				if (issethit )
				{
					if (PC == BASIC)
						hitimg = IMAGEMANAGER->findImage("기본플레이어피격");
				    else if (PC == NARUTO)
						hitimg = IMAGEMANAGER->findImage("나루토피격");
					else if (PC == LUFFY)
						hitimg = IMAGEMANAGER->findImage("루피피격");
					else if (PC == SONOGONG)
						hitimg = IMAGEMANAGER->findImage("손오공피격");


					hitimg->frameRender(CAMERAMANAGER->getWorldDC(), _player.rc.left, _player.rc.top, hitcurrentFrameX, hitcurrentFrameY);


				}


			
		}
		if (isskill)
		{

			skillimg->frameRender(CAMERAMANAGER->getWorldDC(), _player.rc.left + errorX, _player.rc.top + errorY, currentFrameX, currentFrameY);
			//오른쪽에너지파
			if (isrightenergy)
			{
				//cout << energyrange << endl;
				energyrange += 80;
				frontenergy->render(CAMERAMANAGER->getWorldDC(), _player.rc.right + 50, _player.rc.top - 70, 0, 0, energyrange, 249);
				_player.skillrc = RectMake(_player.rc.right + 50, _player.rc.top, energyrange, 149);
				if (energyrange > 1500) {
					isrightenergy = false;
					energyrange = 0;
				}
			}
			//왼쪽에너지파
			if (isleftenergy)
			{

				//cout << energyrange << endl;
				energysizex += 80;
				energyrange -= 80;
				backenergy->render(CAMERAMANAGER->getWorldDC(), _player.rc.left - 30 - energysizex, _player.rc.top - 70, energyrange, 0, energysizex, 249);
				_player.skillrc = RectMake(_player.rc.left - 30 - energysizex, _player.rc.top, energysizex, 149);
				if (energyrange < 50) {
					isleftenergy = false;
					energyrange = 1500;
					energysizex = 0;
				}
			}


		}


	


	if (isOnegi)
	{

		Onegi->frameRender(CAMERAMANAGER->getWorldDC(), Onegirc.left , Onegirc.top, OnegiframeX, 0);
	}




	
	_itemMG->render();
	narutoBullet->render();
	itemBullet->render();
	
	
}

void Player::Gravity()
{
	if (_player.isground)
	{
	
		
		jumppower = 0.f;
		gravitiy = 0.f;
		sumgravity = 0.f;
	}
	if (!_player.isground)
	{

		gravitiy = 8.0f;
		jumppower -= sumgravity;
		sumgravity += 0.05f;
		//sumgravity += sumgravity;
		//jumppower -= gravitiy;
		//gravitiy = 4.5f;
		_player.center.y += gravitiy;
	}

}




void Player::Player_Controll()
{
	//&& DATA->playerInfo.skill1cooltime >= 100 && PC != BASIC
	//스킬1    //100은 스킬맥스
	if (KEYMANAGER->isOnceKeyDown('Z')&& DATA->playerInfo.skill4cooltime >= 100 && DATA->playerInfo.isitem)
	{
		SOUNDMANAGER->play("스킬공격", 1.0f);
		for (int i = 0; i < 30; i++)
		{
			itemBullet->bulletFire(_player.rc.right, _player.rc.top + 30, 30 * i, 15);
		}
		DATA->playerInfo.skill4cooltime = 0;
	}

	if (KEYMANAGER->isOnceKeyDown('A')&& DATA->playerInfo.skill1cooltime >= 100 && PC != BASIC  )
	{
		SOUNDMANAGER->play("스킬공격", 1.0f);
		
		DATA->playerInfo.skill1cooltime = 0;
		_player.skillindex = 1;
		if (PC == NARUTO)
		{
			SOUNDMANAGER->play("던질때", 5);
			errorX = -30;
			errorY = 0;
			if (RL)
			{

				SettingSkillImg("나루토스킬1", 0, 0, 5, true);
				narutoBullet->bulletFire(_player.rc.right, _player.rc.top+30, 0, 15);

				
			}
			else 
			{
				SettingSkillImg("나루토스킬1", 4, 1, 5, true);
				narutoBullet->bulletFire(_player.rc.left, _player.rc.top+30, 180*DO, 15);
			}

		}



		if (PC == LUFFY)
		{
			errorX = -80;
			errorY = -20;
			if (RL)
			{

				SettingSkillImg("루피난타", 0, 0, 8, true);
				
				//skillMaxcount = 30;
					_player.skillrc = RectMakeCenter(_player.center.x + 100, _player.center.y, 200, 200);
			}
			else
			{
				SettingSkillImg("루피난타", 7, 1, 8, true);
				_player.skillrc = RectMakeCenter(_player.center.x - 100, _player.center.y, 200, 200);
			}

		}

		if (PC == SONOGONG)
		{
			
			errorX = -50;
			errorY = -40;
			if (RL)
			{
				energyrange = 0;
				isrightenergy = true;
				
				SettingSkillImg("손오공에너지파", 0, 0, 11, true);
				
			}
			else
			{
				
				energyrange = 1500;
				isleftenergy = true;
				
				cout << energysizex<<endl;
				SettingSkillImg("손오공에너지파", 10, 1, 11, true);
				
			}

		}

	}
	//스킬2
	if (KEYMANAGER->isOnceKeyDown('S') && DATA->playerInfo.skill2cooltime >= 100 && PC != BASIC )
	{
		
		DATA->playerInfo.skill2cooltime = 0;
		_player.skillindex = 2;
		if (PC == NARUTO)
		{
			SOUNDMANAGER->play("나선환", 5);
			errorX = -40;
			errorY = -30;
			if (RL)
			{
				_player.skillrc = RectMakeCenter(_player.center.x + 150, _player.center.y, 300, 200);
				SettingSkillImg("나루토나선환", 0, 0, 15, true);

			}
			else
			{
				_player.skillrc = RectMakeCenter(_player.center.x - 150, _player.center.y, 300, 200);
				SettingSkillImg("나루토나선환", 14, 1, 15, true);
			}

		}

		if (PC == LUFFY)
		{
			SOUNDMANAGER->play("루피바주카포", 5);
			errorX = -180;
			errorY = -6;
			if (RL)
			{
				_player.skillrc = RectMakeCenter(_player.center.x + 100, _player.center.y, 300, 200);
				SettingSkillImg("루피바주카포", 0, 0, 8, true);

			}
			else
			{
				_player.skillrc = RectMakeCenter(_player.center.x - 100, _player.center.y, 300, 200);
				SettingSkillImg("루피바주카포", 7, 1, 8, true);
			}

		}

		if (PC == SONOGONG)
		{
			SOUNDMANAGER->play("원기옥", 5);
			OnegiframeX = 0;
			errorX = -50;
			errorY = -50;
			if (RL)
			{
				
				isOnegi = true;
				Onegirc = RectMakeCenter(_player.center.x , _player.center.y-400, 500, 500);
				SettingSkillImg("손오공원기옥", 0, 0, 14, true);
				//EFFECTMANAGER->play("손오공기이펙트", _player.center.x, _player.center.y - 60);
			}
			else
			{

				isOnegi = true;
				Onegirc = RectMakeCenter(_player.center.x, _player.center.y - 400, 500, 500);
				SettingSkillImg("손오공원기옥", 13, 1, 14, true);
				//EFFECTMANAGER->play("손오공기이펙트", _player.center.x, _player.center.y - 60);
			}

		}

	}
	//스킬3
	if (KEYMANAGER->isOnceKeyDown('D') && DATA->playerInfo.skill3cooltime>=100 && PC != BASIC)
	{
		SOUNDMANAGER->play("스킬공격", 5);
		DATA->playerInfo.skill3cooltime = 0;
		_player.skillindex = 3;
		if (PC == NARUTO)
		{
			
			int rand = RND->getFromIntTo(1, 4);
			//변신성공
			if (1 < rand)
			{
				SOUNDMANAGER->play("나루토괴물", 5);
				errorX = -70;
				errorY = -50;
				if (RL)
				{
					_player.skillrc = RectMakeCenter(_player.center.x + 150, _player.center.y, 200, 200);
					SettingSkillImg("나루토변신", 0, 0, 20, true);

				}
				else
				{
					_player.skillrc = RectMakeCenter(_player.center.x - 150, _player.center.y, 200, 200);
					SettingSkillImg("나루토변신", 19, 1, 20, true);
				}
			}
			//변신실패
			else if (1 == rand) {
				errorX = -30;
				errorY = -25;
				if (RL)
				{

					SettingSkillImg("나루토변신실패", 0, 0, 14, true);

				}
				else
				{
					SettingSkillImg("나루토변신실패", 13, 1, 14, true);
				}
			}

		}


		if (PC == LUFFY)
		{
			errorX = -50;
			errorY = -70;
			if (RL)
			{

				SettingSkillImg("루피스프링", 0, 0, 11, true);
				_player.skillrc = RectMakeCenter(_player.center.x , _player.center.y, 400, 400);
			}
			else
			{
				SettingSkillImg("루피스프링", 10, 1, 11, true);
				_player.skillrc = RectMakeCenter(_player.center.x , _player.center.y, 400, 400);
			}

		}

		if (PC == SONOGONG)
		{
			//cout << PC << endl;
			errorX = -30;
			errorY = -25;
			if (RL)
			{
				EFFECTMANAGER->play("손오공기이펙트", _player.center.x, _player.center.y - 60);
				SettingSkillImg("손오공궁극기", 0, 0, 10, true);
				_player.skillrc = RectMake(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);

			}
			else
			{
				EFFECTMANAGER->play("손오공기이펙트", _player.center.x, _player.center.y - 60);
				SettingSkillImg("손오공궁극기", 9, 1, 10, true);
				_player.skillrc = RectMake(CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
			}
			
			//cout << PC << endl;
			Fexit = false;
			

		}



	}


	if (!isskill && !issethit)
	{


		//위로 공격
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (KEYMANAGER->isOnceKeyDown('X'))
			{
				SOUNDMANAGER->play("일반공격", 5);
				ishit = true;
				//나루토
				if (PC == NARUTO)
				{
					errorX = -40;
					errorY = -60;
					if (RL)
					{
						_player.isCommand = true;
						SettingSkillImg("나루토위공격", 0, 0, 7, true);
						PS = PLAYER_RIGHT_ATK;
					}
					else
					{
						_player.isCommand = true;
						SettingSkillImg("나루토위공격", 6, 1, 7, true);
						PS = PLAYER_LEFT_ATK;
					}
				}
				//루피
				if (PC == LUFFY)
				{
					errorX = -40;
					errorY = -160;
					if (RL)
					{
						_player.isCommand = true;
						SettingSkillImg("루피위공격", 0, 0, 8, true);
						PS = PLAYER_RIGHT_ATK;
					}
					else
					{
						_player.isCommand = true;
						SettingSkillImg("루피위공격", 7, 1, 8, true);
						PS = PLAYER_LEFT_ATK;
					}
				}
				//손오공
				if (PC == SONOGONG)
				{
					errorX = -40;
					errorY = -40;
					if (RL)
					{
						_player.isCommand = true;
						SettingSkillImg("손오공위공격", 0, 0, 6, true);
						PS = PLAYER_RIGHT_ATK;

					}
					else
					{
						_player.isCommand = true;
						SettingSkillImg("손오공위공격", 5, 1, 6, true);
						PS = PLAYER_LEFT_ATK;
					}
				}

			}
		}
		//밑으로 점프
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (KEYMANAGER->isOnceKeyDown('C'))
			{
				jumppower = -30.f;
				_player.isground = false;
				_player.isjump = true;
				if (PS == PLAYER_RIGHT_IDLE || PS == PLAYER_RIGHT_MOVE)PS = PLAYER_RIGHT_JUMP;
				if (PS == PLAYER_LEFT_IDLE || PS == PLAYER_LEFT_MOVE)PS = PLAYER_LEFT_JUMP;
				BasicPlayerAni->start();
			}
			
			if (KEYMANAGER->isOnceKeyDown('X'))
			{
				SOUNDMANAGER->play("일반공격", 5);
				ishit = true;


				//나루토밑으로공격
				if (PC == NARUTO)
				{
					errorX = -40;
					errorY = -25;
					if (RL)
					{
						PS = PLAYER_RIGHT_ATK;
						_player.isCommand = true;
						SettingSkillImg("나루토아래공격", 0, 0, 7, true);

					}
					else
					{
						_player.isCommand = true;
						PS = PLAYER_LEFT_ATK;
						SettingSkillImg("나루토아래공격", 6, 1, 7, true);
					}
				}



				//루피 밑으로 공격
				if (PC == LUFFY)
				{
					errorX = -150;
					errorY = 0;
					if (RL)
					{
						PS = PLAYER_RIGHT_ATK;
						_player.isCommand = true;
						SettingSkillImg("루피아래공격", 0, 0, 6, true);

					}
					else
					{
						PS = PLAYER_LEFT_ATK;
						_player.isCommand = true;
						SettingSkillImg("루피아래공격", 5, 1, 6, true);
					}
				}

				//손오공밑으로공격

				if (PC == SONOGONG)
				{
					errorX = -40;
					errorY = -50;
					if (RL)
					{
						PS = PLAYER_RIGHT_ATK;
						_player.isCommand = true;
						SettingSkillImg("손오공아래공격", 0, 0, 5, true);

					}
					else
					{
						PS = PLAYER_LEFT_ATK;
						_player.isCommand = true;
						SettingSkillImg("손오공아래공격", 4, 1, 5, true);
					}
				}

			}



		}


		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{

			BasicPlayerAni->start();

		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{

			if (PS != PLAYER_LEFT_ATK)
			{

				_player.center.x -= (_player.speed +DATA->playerInfo.playerSPEED);

				if (PS != PLAYER_RIGHT_JUMP && PS != PLAYER_LEFT_JUMP)PS = PLAYER_LEFT_MOVE;

			}
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{

			if (PS != PLAYER_RIGHT_JUMP && PS != PLAYER_LEFT_JUMP)PS = PLAYER_LEFT_IDLE;
			BasicPlayerAni->start();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{

			BasicPlayerAni->start();


		}


		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (PS != PLAYER_RIGHT_ATK)
			{
				_player.center.x += (_player.speed + DATA->playerInfo.playerSPEED);

				if (PS != PLAYER_RIGHT_JUMP && PS != PLAYER_LEFT_JUMP)PS = PLAYER_RIGHT_MOVE;

			}


		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{

			if (PS != PLAYER_RIGHT_JUMP && PS != PLAYER_LEFT_JUMP)PS = PLAYER_RIGHT_IDLE;
			BasicPlayerAni->start();
		}

		if (KEYMANAGER->isOnceKeyDown('C'))
		{

			if (PS == PLAYER_RIGHT_IDLE || PS == PLAYER_RIGHT_MOVE)PS = PLAYER_RIGHT_JUMP;
			if (PS == PLAYER_LEFT_IDLE || PS == PLAYER_LEFT_MOVE)PS = PLAYER_LEFT_JUMP;

			BasicPlayerAni->start();

			jumppower = 22.5f;
			sumgravity = 0.4f;
			_player.isground = false;
			_player.isjump = true;
			jumpcount++;
		}



		//cout << elapsedTime << endl;



		//공격
		if (PS == PLAYER_RIGHT_ATK)
		{
			
			if(ishit)
				_player.atkrc = RectMakeCenter(_player.center.x+50 , _player.center.y, 110+ DATA->playerInfo.playerATKRANGE, 100);

			
				
			
			
			
		}
		else if (PS == PLAYER_LEFT_ATK)
		{
			if (ishit)
			_player.atkrc = RectMakeCenter(_player.center.x - 40, _player.center.y, 110 + DATA->playerInfo.playerATKRANGE, 100);
		
		}
		else
		{
		
			_player.atkrc = RectMakeCenter(_player.center.x, _player.center.y, 0, 0);
		}




		if (_player.isjump && jumpcount < 3)
		{

			_player.center.y -= jumppower;

			//jumppower -= gravitiy;

			if (jumppower < -1.f)
			{
				jumppower = -1.f;
			}

		}

	}
}




void Player::Player_State()
{
	
	switch (PS)
	{
	case PLAYER_LEFT_IDLE:
	{
		RL = false;
			BasicPlayerAni->setFPS(1);
			BasicPlayerAni->setPlayFrame(8, 15, false, true);
		
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			SOUNDMANAGER->play("일반공격", 5);
			ishit = true;
			
			PS=PLAYER_LEFT_ATK;

			BasicPlayerAni->start();


		}

		break;
	}
	case PLAYER_RIGHT_IDLE:
	{
		RL = true;
		BasicPlayerAni->setFPS(1);
		BasicPlayerAni->setPlayFrame(0, 7, true, true);

		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			SOUNDMANAGER->play("일반공격", 5);
			ishit = true;
			PS = PLAYER_RIGHT_ATK;
		
			BasicPlayerAni->start();

		}
		break;
	}
	case PLAYER_LEFT_MOVE:
	{
		RL = false;
		BasicPlayerAni->setFPS(1);
		BasicPlayerAni->setPlayFrame(24, 31, false, true);
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			ishit = true;

			PS = PLAYER_LEFT_ATK;

			BasicPlayerAni->start();


		}
		break;
	}
	case PLAYER_RIGHT_MOVE:
	{
		RL = true;
		BasicPlayerAni->setFPS(1);
		BasicPlayerAni->setPlayFrame(16, 23, false, true);
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			SOUNDMANAGER->play("일반공격", 5);
			ishit = true;
			PS = PLAYER_RIGHT_ATK;

			BasicPlayerAni->start();

		}
		break;
	}
	case PLAYER_LEFT_JUMP:
	{
		RL = false;
		if (PC == BASIC)
		{
			/*int leftjump[] = { 53,52,51 };
			BasicPlayerAni->setFPS(1);
			BasicPlayerAni->setPlayFrame(leftjump, 3, false);*/
			BasicPlayerAni->setFPS(1);
			BasicPlayerAni->setPlayFrame(60, 63, true, false);
		}
		else if (PC == NARUTO || PC == LUFFY || PC == SONOGONG)
		{
			
			BasicPlayerAni->setFPS(1);
			BasicPlayerAni->setPlayFrame(60, 63, true, false);

		}
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			SOUNDMANAGER->play("일반공격", 5);
			ishit = true;

			PS = PLAYER_LEFT_ATK;

			BasicPlayerAni->start();


		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			
			PS = PLAYER_RIGHT_JUMP;

		}
		if (_player.isground)
		{
			PS = PLAYER_LEFT_IDLE;
			BasicPlayerAni->start();
		}

		break;
	}
	case PLAYER_RIGHT_JUMP:
	{
		RL = true;
		if (PC == BASIC)
		{
			/*int rgihtjump[] = { 48,49,50 };
			BasicPlayerAni->setFPS(1);
			BasicPlayerAni->setPlayFrame(rgihtjump, 3, false);*/
			BasicPlayerAni->setFPS(1);
		    BasicPlayerAni->setPlayFrame(56, 59, false, false);
		}
		else if (PC == NARUTO || PC == LUFFY || PC == SONOGONG)
		{

			BasicPlayerAni->setFPS(1);
			BasicPlayerAni->setPlayFrame(56, 59, false, false);

		}
		
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			SOUNDMANAGER->play("일반공격", 5);
			ishit = true;
			PS = PLAYER_RIGHT_ATK;

			BasicPlayerAni->start();

		}

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{

			PS = PLAYER_LEFT_JUMP;

		}
		if (_player.isground)
		{
			PS = PLAYER_RIGHT_IDLE;
			BasicPlayerAni->start();
		}
	
	break;
	}
	case PLAYER_LEFT_ATK:
	{
		RL = false;
		if (PC == BASIC)
		{
			/*int leftatk[] = { 37,36,35 };
			BasicPlayerAni->setFPS(10);
			BasicPlayerAni->setPlayFrame(leftatk, 3, false);*/
			BasicPlayerAni->setFPS(10);
			BasicPlayerAni->setPlayFrame(36, 39, true, false);
		}
		else if(atktime<3&&(PC == NARUTO || PC == LUFFY || PC == SONOGONG))
		{
			BasicPlayerAni->setFPS(10);
			BasicPlayerAni->setPlayFrame(36, 39, true, false);
		}
		else if (atktime >=3 && (PC == NARUTO || PC == LUFFY || PC == SONOGONG))
		{
			BasicPlayerAni->setFPS(10);
			BasicPlayerAni->setPlayFrame(44, 47, true, false);
			if (atktime > 4)
			{
				atktime = 0;
			}
			
		}
		// 공격 충돌 사각형 
		//_player.atkrc = RectMakeCenter(_player.center.x - 50, _player.center.y, 50, 100);
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			SOUNDMANAGER->play("일반공격", 5);
			ishit = true;
			atktime++;
			//BasicPlayerAni->start();

		}
		anicount++;
		if (anicount % 10 == 0)
		{
			if (_player.isground) {
				PS = PLAYER_LEFT_IDLE;
			}
			if (!_player.isground) {
				PS = PLAYER_LEFT_JUMP;
			}
			BasicPlayerAni->start();
			if (atktime > 3)
			{
				atktime = 0;
			}
			
		}


		/*if (KEYMANAGER->isOnceKeyUp('X'))
		{
			atktime++;
			if (_player.isground) {
				PS = PLAYER_LEFT_IDLE;
			}
			if (!_player.isground) {
				PS = PLAYER_LEFT_JUMP;
			}
			
			BasicPlayerAni->start();
		}*/
	
		break;
	}
	case PLAYER_RIGHT_ATK:
	{
		RL = true;
		if (PC == BASIC)
		{
			BasicPlayerAni->setFPS(10);
			BasicPlayerAni->setPlayFrame(32, 35, false, false);
		}
		else if (atktime < 3 && (PC == NARUTO || PC == LUFFY || PC == SONOGONG))
		{
			BasicPlayerAni->setFPS(10);
			BasicPlayerAni->setPlayFrame(32, 35, false, false);

		}
		else if (atktime >= 3 && (PC == NARUTO || PC == LUFFY || PC == SONOGONG))
		{
			
			BasicPlayerAni->setFPS(10);
			BasicPlayerAni->setPlayFrame(40, 43, false, false);
			if (atktime > 4)
			{
				atktime = 0;
			}
		}
		// 공격 충돌 사각형 
		
		
		
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			SOUNDMANAGER->play("일반공격", 5);
			ishit = true;
			atktime++;
			BasicPlayerAni->start();

		}

		anicount++;
		if (anicount % 10 == 0)
		{
			if (_player.isground) {
				PS = PLAYER_RIGHT_IDLE;
			}
			if (!_player.isground) {
				PS = PLAYER_RIGHT_JUMP;
			}
			anicount = 0;
			BasicPlayerAni->start();
		}


		/*if (KEYMANAGER->isOnceKeyUp('X'))
		{
			atktime++;
			if (_player.isground) {
				PS = PLAYER_RIGHT_IDLE;
			}
			if (!_player.isground) {
				PS = PLAYER_RIGHT_JUMP;
			}
			BasicPlayerAni->start();
		}*/
		
		break;
	}


	

	}
}

void Player::WindowMapCollison()
{
	if (_player.center.x < 0) {
		_player.center.x = 0;
	}
	if (_player.center.x > CAMERAMANAGER->get_MaxWorldSizeX()) {
		_player.center.x = CAMERAMANAGER->get_MaxWorldSizeX();
	}
}

//void Player::ChangeState(string key)
//{
//	PlayerStateBase* state = states[key];
//	state->Enter();
//	currentState = state;
//
//}

void Player::PlayerTypeChange()
{
	//DATA->playerInfo.playertype = playertype;

	if (DATA->playerInfo.playertype > 3)
	{
		DATA->playerInfo.playertype = 0;
		PC = BASIC;
	}


	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && DATA->playerInfo.charslot.size()>1)
	{
		int temp;
		temp = DATA->playerInfo.charslot[0];
		DATA->playerInfo.charslot[0] = DATA->playerInfo.charslot[1];
		DATA->playerInfo.charslot[1] = temp;
		

		//DATA->playerInfo.playertype++;


		if (DATA->playerInfo.playertype == 0)
		{
			//PC = BASIC;

		}
		else if (DATA->playerInfo.playertype == 1)
		{
			//PC = NARUTO;
			EFFECTMANAGER->play("연막이펙트", _player.center.x, _player.center.y);
		}
		else if (DATA->playerInfo.playertype == 2)
		{
			//PC = LUFFY;
			EFFECTMANAGER->play("빛이펙트", _player.center.x, _player.center.y);
		}
		else if (DATA->playerInfo.playertype == 3)
		{
			//PC = SONOGONG;
			EFFECTMANAGER->play("파란빛이펙트", _player.center.x, _player.center.y);
		}
	}

	switch (DATA->playerInfo.playertype)
	{
	case BASIC:
		PC = BASIC;
		basicplayer = IMAGEMANAGER->findImage("기본캐릭터");
		break;
	case NARUTO:
		PC = NARUTO;
		basicplayer = IMAGEMANAGER->findImage("나루토캐릭터");
		break;
	case LUFFY:
		PC = LUFFY;
		basicplayer = IMAGEMANAGER->findImage("루피캐릭터");
		break;
	case SONOGONG:
		PC = SONOGONG;
		basicplayer = IMAGEMANAGER->findImage("손오공캐릭터");
		break;
	}

}

void Player::SkillFrame()
{
	if (isskill)
	{
	
		//오른쪽 일때 프레임 돌리기
		if (RL)
		{
			framecount++;
			if (framecount %3 == 0)
			{
				currentFrameX++;
			}

			if (currentFrameX == MaxFrameX)
			{
				isskill = false;
			}
		}
		//왼쪽일때 프레임 돌리기
		else
		{
			framecount++;
			if (framecount % 3 == 0)
			{
				currentFrameX--;
			}

			if (currentFrameX == 0)
			{
				isskill = false;
			}

		}

	}

	else
	{
		if (issethit)
		{
			if (RL)
			{
				hitcurrentFrameY = 0;
				hitframecount++;
				if (hitframecount % 5 == 0)
				{
					hitcurrentFrameX++;

					hitframecount = 0;
				}

				if (hitcurrentFrameX == hitimg->getMaxFrameX())
				{
					issethit = false;
					hitcurrentFrameX = 0;
				}

			}
			else

			{
				hitcurrentFrameY = 1;
				hitframecount++;
				if (hitframecount % 5 == 0)
				{
					hitcurrentFrameX++;

					hitframecount = 0;
				}

				if (hitcurrentFrameX == hitimg->getMaxFrameX())
				{
					hitcurrentFrameX = 0;
					issethit = false;
				}
			}
		}

	}
}

void Player::SettingSkillImg(string skillname, int _currentFrameX, int _currentFrameY, int _MaxFrameX, bool _isskill)
{
	skillimg = IMAGEMANAGER->findImage(skillname);
	currentFrameX = _currentFrameX;
	currentFrameY = _currentFrameY;
	MaxFrameX = _MaxFrameX;
	isskill = _isskill;
}

void Player::EndSkillRect()
{
	if (!isskill)
	{
		
			_player.skillrc = RectMake(0, 0, 0, 0);
		
	}

	

}

void Player::OneGi()
{

	if (isOnegi)
	{
		
		Onegicount++;
			if (Onegicount % 2 == 0&&OnegiframeX < 7)
			{
				OnegiframeX++;
				Onegicount = 0;
			}
			//cout << OnegiframeX << endl;
	
			if (OnegiframeX == 7)
			{
				if (RL)
				{
					Onegirc.left += 80;
					Onegirc.right += 80;
				}
				else
				{
					Onegirc.left -= 80;
					Onegirc.right -= 80;
				}
				Onegirc.top += 20;
				Onegirc.bottom += 20;
				if (Onegirc.left > CAMERAMANAGER->get_CameraX() + WINSIZEX ||
					Onegirc.right < CAMERAMANAGER->get_CameraX())
				{
					isOnegi = false;
				}
			}
	}


}

void Player::SetDragon()
{
	Scnt++;
	if(Scnt % 2==0)
	{
		
		if (!Fexit)
		{
		  FrameX++;
		  if (FrameX > Dragon->getMaxFrameX() && Dragon == IMAGEMANAGER->findImage("신룡1"))
		  {
			  
			  Dragon = IMAGEMANAGER->findImage("신룡2");
			  FrameX = 0;
			  
		  }
		  if (FrameX > Dragon->getMaxFrameX() && Dragon == IMAGEMANAGER->findImage("신룡2"))
		  {
			  Dragon = IMAGEMANAGER->findImage("신룡1");
			  Fexit = true;
			  FrameX = 0;
		  }
		}
		Scnt = 0;
	}
}



void Player::MonsterCollison()
{


	for (int i = 0; i < _monsterMG->getVmonster().size(); i++)
	{
		RECT monsterRC = _monsterMG->getVmonster()[i]->GetMonsterRC();
		for (int j = 0; j < narutoBullet->getVBullet().size(); j++)
		{
			RECT temp;
			RECT rc = narutoBullet->getVBullet()[j]->rc;


			if (IntersectRect(&temp, &rc, &monsterRC))
			{
				EFFECTMANAGER->play("기본피격", (rc.left + rc.right)/2, (rc.top + rc.bottom) / 2);
				narutoBullet->removeBullet(j);
				_monsterMG->getVmonster()[i]->hitDamage(100);
				break;
			}
		}

		for (int k = 0; k < itemBullet->getVBullet().size(); k++)
		{
			RECT temp;
			RECT rc = itemBullet->getVBullet()[k]->rc;

			
			if (IntersectRect(&temp, &rc, &monsterRC))
			{
				EFFECTMANAGER->play("기본피격", (rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2);
				itemBullet->removeBullet(k);
				_monsterMG->getVmonster()[i]->hitDamage(10);
				break;
			}
		}


	}

	//if (_monsterMG->getVmonster().size() > 0)
	//{
	//	for (int i = 0; i < _monsterMG->getVmonster().size(); i++)
	//	{
	//		if (_monsterMG->getVmonster().size() <= 0)return;

	//		RECT monsterRC = _monsterMG->getVmonster()[i]->GetMonsterRC();
	//		
	//		RECT temp;

	//		//플레이어 일반공격
	//		if (IntersectRect(&temp, &monsterRC, &_player.atkrc))
	//		{
	//			if (!_player.isCommand)
	//			{
	//				_monsterMG->getVmonster()[i]->hitDamage(8);
	//				EFFECTMANAGER->play("기본피격", RND->getFromIntTo(monsterRC.left, monsterRC.right)
	//					, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));
	//				
	//				_player.atkrc = RectMakeCenter(_player.center.x, _player.center.y, 0, 0);
	//				ishit = false;
	//			}

	//			if (_player.isCommand)
	//			{
	//				_monsterMG->getVmonster()[i]->hitDamage(40);
	//				EFFECTMANAGER->play("기본피격", RND->getFromIntTo(monsterRC.left, monsterRC.right)
	//					, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));
	//				
	//				_player.atkrc = RectMakeCenter(_player.center.x, _player.center.y, 0, 0);
	//				ishit = false;
	//				_player.isCommand = false;
	//			}
	//		}

	//		//플레이어 스킬공격들
	//		
	//			if (IntersectRect(&temp, &monsterRC, &_player.skillrc))
	//			{
	//				if (PC == NARUTO)
	//				{
	//					_monsterMG->getVmonster()[i]->hitDamage(2);
	//					EFFECTMANAGER->play("기본피격", RND->getFromIntTo(monsterRC.left, monsterRC.right)
	//						, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));
	//					if (_player.skillindex == 2)
	//					{
	//						EFFECTMANAGER->play("태풍", RND->getFromIntTo(monsterRC.left, monsterRC.right)
	//							, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));
	//					}
	//					


	//				}
	//				else if (PC == LUFFY)
	//				{
	//					_monsterMG->getVmonster()[i]->hitDamage(3);
	//					EFFECTMANAGER->play("마구패", RND->getFromIntTo(monsterRC.left, monsterRC.right)
	//						, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));
	//				}
	//				else if (PC == SONOGONG)
	//				{

	//					if (_player.skillindex == 1)
	//					{
	//						_monsterMG->getVmonster()[i]->hitDamage(2);
	//						EFFECTMANAGER->play("태풍", RND->getFromIntTo(monsterRC.left, monsterRC.right)
	//							, RND->getFromIntTo(monsterRC.top , monsterRC.bottom ));
	//					}


	//					if (_player.skillindex == 3)
	//					{
	//						_monsterMG->getVmonster()[i]->hitDamage(2);
	//						EFFECTMANAGER->play("번개", RND->getFromIntTo(monsterRC.left, monsterRC.right)
	//							, RND->getFromIntTo(monsterRC.top - 100, monsterRC.bottom - 100));
	//					}
	//				}



	//			}
	//			//원기옥
	//			if (IntersectRect(&temp, &monsterRC, &Onegirc))
	//			{
	//				_monsterMG->getVmonster()[i]->hitDamage(3);
	//				EFFECTMANAGER->play("마구패", RND->getFromIntTo(monsterRC.left, monsterRC.right)
	//					, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));

	//			}

	//			//몬스터 피가 0 되면 죽이기
	//		if (_monsterMG->getVmonster()[i]->getHP() <= 0)
	//		{
	//			
	//				for (int i = 0; i < 5; i++)
	//				{
	//					_itemMG->set_Money((monsterRC.right + monsterRC.left) / 2, _monsterMG->getVmonster()[i]->GetItemDropRc().top);
	//				}
	//			
	//			
	//			cout << _monsterMG->getVmonster()[i]->GetMonsterPos().x<< "," << _monsterMG->getVmonster()[i]->GetMonsterPos().y << endl;
	//			_monsterMG->RemoveMonster(i);
	//			break;

	//		}

	//	}
	//}

}

void Player::PlayerAndItemCollison()
{
	for (int i = 0; i < _itemMG->getVItem().size(); i++)
	{





	}

}


//
//void PlayerNaruto::Enter()
//{
//}
//
//void PlayerNaruto::Update()
//{
//}
//
//
//
//void PlayerLuffy::Enter()
//{
//
//}
//
//void PlayerLuffy::Update()
//{
//
//}