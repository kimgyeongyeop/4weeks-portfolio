#include "stdafx.h"
#include "MonsterManager.h"
#include "Player.h"

MonsterManager::MonsterManager()
{
}


MonsterManager::~MonsterManager()
{
}

HRESULT MonsterManager::init()
{

	monster2bullet = new Bullet;
	monster2bullet->init("¸ó½ºÅÍ²ÉÃÑ¾Ë", 50, 600);
	monster3bullet = new Bullet;
	monster3bullet->init("ÇÇÄÝ·ÎÃÑ¾Ë", 50, 600);
	monster5bullet = new Bullet;
	monster5bullet->init("ÇØÀûÃÑ¾Ë", 100, 1200);
	monster7bullet = new Bullet;
	monster7bullet->init("»õÃÑ¾Ë", 30, 1200);
	bossbullet = new Bullet;
	bossbullet ->init("º¸½ºÃÑ¾Ë", 100, 1300);
	angle = 0;
	return S_OK;
}

void MonsterManager::release()
{
}

void MonsterManager::update()
{
	//cout << DATA->playerInfo.playerHP << endl;
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		(*_viMonster)->update();
	}
	

	MonsterBulletFire();

	monster2bullet->update();
	monster3bullet->update();
	monster5bullet->update();
	monster7bullet->update();
	bossbullet->update();
	Collision();
}

void MonsterManager::render()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{
		(*_viMonster)->render();
	}
	monster2bullet->render();
	monster3bullet->render();
	monster5bullet->render();
	monster7bullet->render();
	bossbullet->render();
	//CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
}

void MonsterManager::RemoveMonster(int arr)
{
	
		
		_vMonster.erase(_vMonster.begin() + arr);
	
}

void MonsterManager::set_BasicMonster(POINT mosterpos)
{

		BasicMonster* monster1;
		monster1 = new BasicMonster;


		monster1->init(PointMake(mosterpos.x, mosterpos.y));
		_vMonster.push_back(monster1);
	
}

void MonsterManager::set_FlowerMonster(POINT mosterpos)
{
	FlowerMonster* monster2;
	monster2 = new FlowerMonster;

	monster2-> init(PointMake(mosterpos.x, mosterpos.y));
	_vMonster.push_back(monster2);
}

void MonsterManager::set_PicoloMonster(POINT mosterpos)
{
	PicoloMonster* monster3;
	monster3 = new PicoloMonster;
	monster3->init(PointMake(mosterpos.x, mosterpos.y));
	_vMonster.push_back(monster3);
}

void MonsterManager::set_PoisonMonster(POINT mosterpos)
{
	PoisonMonster* monster4;
	monster4 = new PoisonMonster;
	monster4->init(PointMake(mosterpos.x, mosterpos.y));
	_vMonster.push_back(monster4);
}

void MonsterManager::set_PirateMonster(POINT mosterpos)
{
	PirateMonster* monster5;
	monster5 = new PirateMonster;
	monster5->init(PointMake(mosterpos.x, mosterpos.y));
	_vMonster.push_back(monster5);
}

void MonsterManager::set_NavyMonster(POINT mosterpos)
{
	NavyMonster* monster6;
	monster6 = new NavyMonster;
	monster6->init(PointMake(mosterpos.x, mosterpos.y));
	_vMonster.push_back(monster6);
}

void MonsterManager::set_GetAngleMonster(POINT mosterpos)
{
	GetAngleMonster* monster7;
	monster7 = new GetAngleMonster;
	monster7->init(PointMake(mosterpos.x, mosterpos.y));
	_vMonster.push_back(monster7);
}

void MonsterManager::set_Boss(POINT mosterpos)
{
	Boss* monster8;
	monster8 = new Boss;
	monster8->init(PointMake(mosterpos.x, mosterpos.y));
	_vMonster.push_back(monster8);
}



void MonsterManager::MonsterBulletFire()
{
	for (_viMonster = _vMonster.begin(); _viMonster != _vMonster.end(); ++_viMonster)
	{

		//¸ó½ºÅÍ ÀÎµ¦½º 2ÀÏ °æ¿ì
		if ((*_viMonster)->GetMonsterIndex() == 2)
		{
			if ((*_viMonster)->MonsterBulletFire())
			{
				RECT rc = (*_viMonster)->GetMonsterRC();

				monster2bullet->bulletFire((rc.right + rc.left) / 2,
					(rc.bottom + rc.top) / 2-10, (*_viMonster)->GetBulletAngle(), 7.0f);
			}
		}

		//¸ó½ºÅÍ ÀÎµ¦½º 3ÀÏ °æ¿ì
		if ((*_viMonster)->GetMonsterIndex() == 3)
		{
			if ((*_viMonster)->MonsterBulletFire())
			{
				RECT rc = (*_viMonster)->GetMonsterRC();

				monster3bullet->bulletFire((rc.right + rc.left) / 2,
					(rc.bottom + rc.top) / 2-10, (*_viMonster)->GetBulletAngle(), 10.0f);
			}
		}

		//¸ó½ºÅÍ ÀÎµ¦½º 5ÀÏ °æ¿ì
		if ((*_viMonster)->GetMonsterIndex() == 5)
		{
			if ((*_viMonster)->MonsterBulletFire())
			{
				RECT rc = (*_viMonster)->GetMonsterRC();

				for (int i = 1; i < 7; i++)
				{
					monster5bullet->bulletFire((rc.right + rc.left) / 2,
						(rc.bottom + rc.top) / 2 ,60*i*DO, 8.0f);
				}
			}
		}


		//¸ó½ºÅÍ ÀÎµ¦½º 7ÀÏ °æ¿ì
		if ((*_viMonster)->GetMonsterIndex() == 7)
		{
			if ((*_viMonster)->MonsterBulletFire())
			{
				RECT rc = (*_viMonster)->GetMonsterRC();
				
				monster7bullet->bulletFire((rc.right + rc.left) / 2,
					(rc.bottom + rc.top) / 2 - 10,
					getAngle((*_viMonster)->GetMonsterPos().x, (*_viMonster)->GetMonsterPos().y, _player->GetPlayerX(), _player->GetPlayerY()),
					10.0f);
			}
		}


		//¸ó½ºÅÍ ÀÎµ¦½º 8ÀÏ °æ¿ì
		if ((*_viMonster)->GetMonsterIndex() == 8)
		{
			if ((*_viMonster)->MonsterBulletFire())
			{
				angle+=3;
				//RECT rc = (*_viMonster)->GetMonsterRC();

				bossbullet->bulletFire((*_viMonster)->GetSkillPosX()+100,
					(*_viMonster)->GetSkillPosY()+100,
					DO*0+angle,
					10.0f);
			}
		}
		


	}

}

void MonsterManager::Collision()
{
	for (int i = 0; i < monster2bullet->getVBullet().size(); i++)
	{
		RECT temp;
		RECT rc = monster2bullet->getVBullet()[i]->rc;


		if (IntersectRect(&temp, &rc, &_player->GetPlayerRC()))
		{
			_player->SetSetHit(true);
			monster2bullet->removeBullet(i);
			DATA->playerInfo.playerHP -= 10;
			break;
		}
	}

	for (int i = 0; i < monster3bullet->getVBullet().size(); i++)
	{
		RECT temp;
		RECT rc = monster3bullet->getVBullet()[i]->rc;


		if (IntersectRect(&temp, &rc, &_player->GetPlayerRC()))
		{
			_player->SetSetHit(true);
			monster3bullet->removeBullet(i);
			DATA->playerInfo.playerHP -= 10;
			break;
		}
	}

	for (int i = 0; i < monster5bullet->getVBullet().size(); i++)
	{
		RECT temp;
		RECT rc = monster5bullet->getVBullet()[i]->rc;


		if (IntersectRect(&temp, &rc, &_player->GetPlayerRC()))
		{
			_player->SetSetHit(true);
			monster5bullet->removeBullet(i);
			DATA->playerInfo.playerHP -= 10;
			break;
		}
	}

	for (int i = 0; i < monster7bullet->getVBullet().size(); i++)
	{
		RECT temp;
		RECT rc = monster7bullet->getVBullet()[i]->rc;


		if (IntersectRect(&temp, &rc, &_player->GetPlayerRC()))
		{
			_player->SetSetHit(true);
			monster7bullet->removeBullet(i);
			DATA->playerInfo.playerHP -= 10;
			break;
		}
	}


	for (int i = 0; i < bossbullet->getVBullet().size(); i++)
	{
		RECT temp;
		RECT rc = bossbullet->getVBullet()[i]->rc;


		if (IntersectRect(&temp, &rc, &_player->GetPlayerRC()))
		{
			_player->SetSetHit(true);
			bossbullet->removeBullet(i);
			DATA->playerInfo.playerHP -= 10;
			break;
		}
	}



}
