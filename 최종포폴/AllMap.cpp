#include "stdafx.h"
#include "AllMap.h"
#include "GameData.h"

GameData* AllMap::gameData = nullptr;

GameData * AllMap::GetData()
{
	return gameData;
}



AllMap::AllMap()
{
	gameData = new GameData;
}


AllMap::~AllMap()
{
}

HRESULT AllMap::init()
{
	monsterandplayercount = 0;
	hitcount = 0;
	bg[0] = new image;
	bg[0] = IMAGEMANAGER->findImage("tutorial_BG_0");
	bg[1] = new image;
	bg[1] = IMAGEMANAGER->findImage("tutorial_BG_1");
	bg[2] = new image;
	bg[2] = IMAGEMANAGER->findImage("tutorial_BG_2");
	
	UiMG = new UiManager;
	UiMG->init();
	ItemMG = new ItemManager;
	ItemMG->init();

	currentpotalframe = 0;
	potalimg = IMAGEMANAGER->findImage("스테이지문");
	player = new Player;
	player->init();
	MonsterMG = new MonsterManager;
	MonsterMG->init();
	MonsterMG->setPlayerMemoryAddressLink(player);
	player->setMemoryAddressLink(MonsterMG);
	istraprender = false;


	
	

	
	return S_OK;
}

void AllMap::release()
{
}

void AllMap::update()
{
	
	
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
	PlayerAndItemCollion();
}

void AllMap::render()
{
	//DATA->playerInfo.currentmap = _MAP;
	//_MAP->render(CAMERAMANAGER->getWorldDC(), 0, 0);
	_MAP->render(CAMERAMANAGER->getWorldDC(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	potalimg ->frameRender(CAMERAMANAGER->getWorldDC(), potalposX, potalposY, currentpotalframe, 0);
	
	//Rectangle(CAMERAMANAGER->getWorldDC(), potal);
	
	//상점스테이지 렉트
	/*for (int i = 0; i < 4; i++)
	{
		Rectangle(CAMERAMANAGER->getWorldDC(), standrc[i]);
	}*/
	
	//MonsterMG->render();
	//GroundRectRender(30);

	 
	if (istraprender)
	{
		trapimg[0]->render(CAMERAMANAGER->getWorldDC(), traprc[0].left, traprc[0].top);
		trapimg[1]->render(CAMERAMANAGER->getWorldDC(), traprc[1].left, traprc[1].top);

	}
	
	player->render();
	MonsterMG->render();
	ItemMG->render();

	if (istostring)
	{

		HFONT myFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "휴면굴림");
		HFONT oldFont = (HFONT)SelectObject(CAMERAMANAGER->getWorldDC(), myFont);
		//SetBkMode(CAMERAMANAGER->getWorldDC(), TRANSPARENT);
	
		char str[30];
			sprintf_s(str, "%s", "F");
		TextOut(CAMERAMANAGER->getWorldDC(), potalposX+110, potalposY, str, strlen(str));

		SelectObject(CAMERAMANAGER->getWorldDC(), oldFont);
		DeleteObject(myFont);
	}

	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	UiMG->render();

	


	TIMEMANAGER->render(getMemDC());
}

void AllMap::CheakLocation()
{

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		

		POINT pos;
		::GetCursorPos(&pos);  //마우스 포인터 좌표 가져와줌
		::ScreenToClient(_hWnd, &pos); // api창안에서만 가져올수있게 보정
		cout << pos.x + CAMERAMANAGER->get_CameraX() << "," << pos.y + CAMERAMANAGER->get_CameraY() << endl;

	}
}
//플레이어랑 맵충돌
void AllMap::PlayerAndMapCollion(int groundRECT, int leftRECT, int rightRECT)
{

	//그냥땅
	for (int i = 0; i < groundRECT; i++)
	{
		//아이템과 땅충돌
	for (int k = 0; k < ItemMG->getVItem().size(); ++k)
		{
			if (ItemMG->getVItem().size() <= 0) return;
			RECT temp;
			if (IntersectRect(&temp, &maprc[i].rc, &ItemMG->getVItem()[k]->GetItemRc()))
			{
				ItemMG->getVItem()[k]->SetIsMove(false);
				ItemMG->getVItem()[k]->SetPositemposY(maprc[i].rc.top);
			}

			//상점 판매대
			for (int q = 0; q < 4; q++)
			{
				if (IntersectRect(&temp, &standrc[q], &ItemMG->getVItem()[k]->GetItemRc()))
				{
					ItemMG->getVItem()[k]->SetIsMove(false);
					ItemMG->getVItem()[k]->SetPositemposY(standrc[q].top);
				}
			}


		}


	//플레이어랑 땅
		RECT rc;


		if (IntersectRect(&rc, &traprc[0], &player->GetPlayerRC()))
		{
			hitcount++;
			if (hitcount == 150)
			{
				DATA->playerInfo.playerHP -= 5;
				hitcount = 0;
			}
		}
		else if (IntersectRect(&rc, &traprc[1], &player->GetPlayerRC()))
		{
			hitcount++;
			if (hitcount == 150)
			{
				DATA->playerInfo.playerHP -= 5;
				hitcount = 0;
			}
		}


		if (IntersectRect(&rc, &maprc[i].rc, &player->GetPlayerRC()))
		{
			blocktype = i;
			
		}
		
		if (player->GetPlayerRC().bottom < maprc[i].rc.top)
		{
			maprc[i].collion = true;
		}
		if (player->GetPlayerRC().bottom > maprc[i].rc.bottom)
		{
			maprc[i].collion = false;
		}

	}

	RECT rc;
	if (IntersectRect(&rc, &maprc[blocktype].rc, &player->GetPlayerRC()) && maprc[blocktype].collion)
	{

		//땅일 때 (중력안줌)
		player->SetJumpPower(0);
		player->SetGravitiy(true);
		player->SetIsJump(false);
		player->SetPlayerY(maprc[blocktype].rc.top - (player->GetPlayerRC().bottom - player->GetPlayerRC().top) / 2 + 1);

		player->SetPlayerRCBottom(maprc[blocktype].rc.top);
		player->SetJumpCount(0);
	}
	else
	{
		//땅이 아니다 (중력줌)
		player->SetGravitiy(false);
	}

	//민욱
	

	//왼쪽에 부딪히는 벽
	for (int i = 0; i < rightRECT; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &rightmaprc[i].rc, &player->GetPlayerRC()))
		{
			player->SetPlayerX(rightmaprc[i].rc.right + 20);
		}
	
	}
	//오른쪽 부딪히는 벽
	for (int i = 0; i < leftRECT; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &leftmaprc[i].rc, &player->GetPlayerRC()))
		{
			player->SetPlayerX(leftmaprc[i].rc.left - 20);
		}

	}
	
}

void AllMap::MonsterAndMapCollion(int groundRECT)
{


	for (int i = 0; i < MonsterMG->getVmonster().size(); ++i)
	{
		if (MonsterMG->getVmonster().size() == 0) return;
		MonsterMG->getVmonster()[i]->SetAngleMonsterPlayerPosX(player->GetPlayerX());

		RECT temp;
		RECT monsterrc = MonsterMG->getVmonster()[i]->GetMonsterRC();
		RECT playerrc = player->GetPlayerRC();
		for (int j = 0; j < groundRECT; j++)
		{
			//몬스터가 해당렉트에 충돌했을때
			if (IntersectRect(&temp, &monsterrc, &maprc[j].rc))
			{
				
					
				
				//충돌한렉트를 몬스터 가져가고
				MonsterMG->getVmonster()[i]->SetMapRect(maprc[j].rc);
				

				//플레이어가 몬스터가 충돌한 렉트와 충돌했을때
				//RECT playerrc = player->GetPlayerRC();
				if (IntersectRect(&temp, &playerrc, &maprc[j].rc))
				{
					//몬스터 인덱스 7이아닐때
					if (MonsterMG->getVmonster()[i]->GetMonsterIndex() != 7)
					{

						MonsterMG->getVmonster()[i]->SetPlayerPos(player->GetPlayerX());
						MonsterMG->getVmonster()[i]->SetPlayerCheak(true);
					}

					//몬스터 인덱스 7일때
					if (MonsterMG->getVmonster()[i]->GetMonsterIndex() == 7)
					{

						if (j - 1 < 0)
						{
							MonsterMG->getVmonster()[i]->SetPlayerPos(player->GetPlayerX());
							MonsterMG->getVmonster()[i]->SetAngleMonsterRECT(maprc[1].rc);
							MonsterMG->getVmonster()[i]->SetPlayerCheak(true);

						}
						else if (j + 1 > groundRECT-1)
						{
							MonsterMG->getVmonster()[i]->SetPlayerPos(player->GetPlayerX());
							MonsterMG->getVmonster()[i]->SetAngleMonsterRECT(maprc[groundRECT - 2].rc);
							MonsterMG->getVmonster()[i]->SetPlayerCheak(true);
						}
						else
						{
							int randomnum = RND->getFromIntTo(-1, 2);
							MonsterMG->getVmonster()[i]->SetPlayerPos(player->GetPlayerX());
							cout << randomnum << endl;
							MonsterMG->getVmonster()[i]->SetAngleMonsterRECT(maprc[j + randomnum].rc);
							
							MonsterMG->getVmonster()[i]->SetPlayerCheak(true);
						}




					}


				}
				else
				{
					MonsterMG->getVmonster()[i]->SetPlayerCheak(false);
				}



			}
		}
	}
}

void AllMap::MonsterAndPlayerCollion()
{

	if (MonsterMG->getVmonster().size() > 0)
	{
		for (int i = 0; i < MonsterMG->getVmonster().size(); i++)
		{
			if (MonsterMG->getVmonster().size() <= 0)return;


			RECT monsterRC = MonsterMG->getVmonster()[i]->GetMonsterRC();

			RECT temp;

			RECT mosterATKrc = MonsterMG->getVmonster()[i]->GetMonsterAtkRC();

		    if(IntersectRect(&temp, &mosterATKrc, &player->GetPlayerRC()))
			{
				
				//monsterandplayercount++;

				
					DATA->playerInfo.playerHP -= 3;
					//monsterandplayercount = 0;
				

			}








			if (MonsterMG->getVmonster()[i]->GetMonsterIndex() == 8)
			{
				RECT bossplayerrc = player->GetPlayerRC();
				MonsterMG->getVmonster()[i]->SetBossPlayerPosX((bossplayerrc.left + bossplayerrc.right) / 2);
				MonsterMG->getVmonster()[i]->SetBossPlayerPosY((bossplayerrc.top + bossplayerrc.bottom) / 2);
			}






			//플레이어 일반공격
			if (IntersectRect(&temp, &monsterRC, &player->GetPlayerAtkRC()))
			{
				SOUNDMANAGER->play("피격", 5);
				MonsterMG->getVmonster()[i]->SetIsstoremonster(false);

				if (!player->GetIsCommand())
				{
					//크리티컬
					
					int rand = RND->getFromIntTo(1, 101);
					cout << rand << endl;
					for (int q = 0; q < DATA->playerInfo.playerCRITICAL; q++)
					{
						if (q == rand)
						{
							MonsterMG->getVmonster()[i]->hitDamage(50 + DATA->playerInfo.playerPOWER);
							EFFECTMANAGER->play("치명타", RND->getFromIntTo(monsterRC.left, monsterRC.right)
								, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));
						}

					}


					//그냥 공격
					MonsterMG->getVmonster()[i]->hitDamage(10+DATA->playerInfo.playerPOWER);
					EFFECTMANAGER->play("기본피격", RND->getFromIntTo(monsterRC.left, monsterRC.right)
						, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));
					RECT nulrc = RectMakeCenter(0, 0, 0, 0);
					player->SetAtkRC(nulrc);
					
					player->SetIsHit(false);
				}

				else if (player->GetIsCommand())
				{
					MonsterMG->getVmonster()[i]->hitDamage(20+DATA->playerInfo.playerPOWER);
					EFFECTMANAGER->play("기본피격", RND->getFromIntTo(monsterRC.left, monsterRC.right)
						, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));
					RECT nulrc = RectMakeCenter(0, 0, 0, 0);
					player->SetAtkRC(nulrc);
					player->SetIsHit(false);
					player->SetIsCommand(false);
				}
			}
		
			//플레이어 스킬공격들

			if (IntersectRect(&temp, &monsterRC, &player->GetPlayerSkillRc()))
			{
				MonsterMG->getVmonster()[i]->SetIsstoremonster(false);

				if (player->GetPlayerPcType() == 1)
				{
					SOUNDMANAGER->play("피격", 5);
					MonsterMG->getVmonster()[i]->hitDamage(2);
					if (player->GetSkiilIndex() == 1)
					{
						EFFECTMANAGER->play("기본피격", RND->getFromIntTo(monsterRC.left, monsterRC.right)
							, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));
					}
					else if (player->GetSkiilIndex() == 2)
					{
						SOUNDMANAGER->play("피격", 5);
						EFFECTMANAGER->play("태풍", RND->getFromIntTo(monsterRC.left, monsterRC.right)
							, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));
					}
					else if (player->GetSkiilIndex() == 3)
					{
						
						if (player->GetPlayerRL())
						{
							EFFECTMANAGER->play("나루토스킬이펙트오른쪽", RND->getFromIntTo(monsterRC.left, monsterRC.right)
								, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));
						}
						else if (!player->GetPlayerRL())
						{
							EFFECTMANAGER->play("나루토스킬이펙트왼쪽", RND->getFromIntTo(monsterRC.left, monsterRC.right)
								, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));
						}
					}



				}
				else if (player->GetPlayerPcType() == 2)
				{
					
					if (player->GetSkiilIndex() == 1 || player->GetSkiilIndex() == 2  || player->GetSkiilIndex() == 3)
					{

						MonsterMG->getVmonster()[i]->hitDamage(3);
						EFFECTMANAGER->play("마구패", RND->getFromIntTo(monsterRC.left, monsterRC.right)
							, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));
					}


				}
				else if (player->GetPlayerPcType() == 3)
				{
					
					if (player->GetSkiilIndex() == 1)
					{
						MonsterMG->getVmonster()[i]->hitDamage(2);
						EFFECTMANAGER->play("태풍", RND->getFromIntTo(monsterRC.left, monsterRC.right)
							, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));
					}


					else if (player->GetSkiilIndex() == 3)
					{
						MonsterMG->getVmonster()[i]->hitDamage(2);
						EFFECTMANAGER->play("번개", RND->getFromIntTo(monsterRC.left, monsterRC.right)
							, RND->getFromIntTo(monsterRC.top - 100, monsterRC.bottom - 100));
					}
				}



			}
			//원기옥
			if (IntersectRect(&temp, &monsterRC, &player->GetPlayerOnegiRC()))
			{
				
				MonsterMG->getVmonster()[i]->SetIsstoremonster(false);

				MonsterMG->getVmonster()[i]->hitDamage(5);
				EFFECTMANAGER->play("마구패", RND->getFromIntTo(monsterRC.left, monsterRC.right)
					, RND->getFromIntTo(monsterRC.top, monsterRC.bottom));

			}




			//몬스터 피가 0 되면 죽이기
			if (MonsterMG->getVmonster()[i]->getHP() <= 0)
			{
				
				//보스몬스터일때
				if(MonsterMG->getVmonster()[i]->GetMonsterIndex()==8)
				{ 
					DATA->playerInfo.Killnum += 1;
					ItemMG->set_FinalBook((monsterRC.right + monsterRC.left) / 2, (monsterRC.top + monsterRC.bottom) / 2);
					MonsterMG->RemoveMonster(i);
					break;
				}
				else
				{
					DATA->playerInfo.Killnum += 1;
					for (int i = 0; i < 5; i++)
					{
						ItemMG->set_Money((monsterRC.right + monsterRC.left) / 2, (monsterRC.top + monsterRC.bottom) / 2);
					}

					int randomHpItem = RND->getFromIntTo(1, 13);

					if (randomHpItem == 1)
					{
						ItemMG->set_Hp((monsterRC.right + monsterRC.left) / 2, (monsterRC.top + monsterRC.bottom) / 2);
					}
					if (randomHpItem == 2)
					{
						ItemMG->set_BigHp((monsterRC.right + monsterRC.left) / 2, (monsterRC.top + monsterRC.bottom) / 2);
					}
					MonsterMG->RemoveMonster(i);
					break;


				}


			}

		}
	}



}

void AllMap::PlayerAndItemCollion()
{
	
	/*if(DATA->playerInfo.charslot.size()>1)  cout << DATA->playerInfo.charslot[0] << ","<< DATA->playerInfo.charslot[1] << endl;
	else {
		cout << DATA->playerInfo.charslot[0] << endl;
	}*/


	for (int i = 0; i < ItemMG->getVItem().size(); ++i)
	{
		if (ItemMG->getVItem().size() <= 0) return;
		RECT temp;
		if (IntersectRect(&temp, &player->GetPlayerRC(), &ItemMG->getVItem()[i]->GetItemRc()))
		{
			if (ItemMG->getVItem()[i]->GetItemIndex() == 1)
			{
				
				
				if (DATA->playerInfo.playerHP < 200) {
					SOUNDMANAGER->play("물먹는소리", 5.0f);
					DATA->playerInfo.playerHP += 30;
					ItemMG->RemoveItem(i);
					break;
				}
				if (DATA->playerInfo.playerHP > 200)
				{
					DATA->playerInfo.playerHP = 200;
				}
			}
			if (ItemMG->getVItem()[i]->GetItemIndex() == 2)
			{
				if (DATA->playerInfo.playerHP < 200) {
					SOUNDMANAGER->play("물먹는소리", 5.0f);
					DATA->playerInfo.playerHP += 60;
					ItemMG->RemoveItem(i);
					break;
				}
				if (DATA->playerInfo.playerHP > 200)
				{
					DATA->playerInfo.playerHP = 200;
				}
			}
			if (ItemMG->getVItem()[i]->GetItemIndex() == 3)
			{
				SOUNDMANAGER->play("동전", 0.3f);
				DATA->playerInfo.playerMoney += 1;
				ItemMG->RemoveItem(i);
				break;
			}
			

			if (ItemMG->getVItem()[i]->GetItemIndex() == 4)
			{
				//아이템 먹었을때 효과 (나루토)
				//DATA->playerInfo.charslot[0] = 1;

				if (KEYMANAGER->isOnceKeyDown('F'))
				{
					if (DATA->playerInfo.charslot.size() < 2) DATA->playerInfo.charslot.push_back(1);
					else
					{
						if (DATA->playerInfo.charslot[0] == DATA->playerInfo.playertype)
						{
						
							ItemMG->set_CharBook((player->GetPlayerRC().right + player->GetPlayerRC().left) / 2,
								(player->GetPlayerRC().top + player->GetPlayerRC().bottom) / 2, DATA->playerInfo.charslot[0]);

							DATA->playerInfo.charslot[0] = 1;
							
						}
						else if (DATA->playerInfo.charslot[1] == DATA->playerInfo.playertype)
						{
							ItemMG->set_CharBook((player->GetPlayerRC().right + player->GetPlayerRC().left) / 2,
								(player->GetPlayerRC().top + player->GetPlayerRC().bottom) / 2, DATA->playerInfo.charslot[1]);

							DATA->playerInfo.charslot[1] = 1;
						}
						/*DATA->playerInfo.charslot.pop_back();
						DATA->playerInfo.charslot.push_back(1);*/
						//DATA->playerInfo.charslot[0] = 3;
					}


					ItemMG->RemoveItem(i);
					break;
				}

			}

			if (ItemMG->getVItem()[i]->GetItemIndex() == 5)
			{
				//아이템 먹었을때 효과 ( 루피)
				//DATA->playerInfo.charslot[0] = 2;

				if (KEYMANAGER->isOnceKeyDown('F'))
				{
					if (DATA->playerInfo.charslot.size() < 2) DATA->playerInfo.charslot.push_back(2);
					else
					{
						if (DATA->playerInfo.charslot[0] == DATA->playerInfo.playertype)
						{
							ItemMG->set_CharBook((player->GetPlayerRC().right + player->GetPlayerRC().left) / 2,
								(player->GetPlayerRC().top + player->GetPlayerRC().bottom) / 2, DATA->playerInfo.charslot[0]);

							DATA->playerInfo.charslot[0] = 2;
						}
						else if (DATA->playerInfo.charslot[1] == DATA->playerInfo.playertype)
						{
							ItemMG->set_CharBook((player->GetPlayerRC().right + player->GetPlayerRC().left) / 2,
								(player->GetPlayerRC().top + player->GetPlayerRC().bottom) / 2, DATA->playerInfo.charslot[1]);
							DATA->playerInfo.charslot[1] = 2;
						}
						/*DATA->playerInfo.charslot.pop_back();
						DATA->playerInfo.charslot.push_back(3);*/
						//DATA->playerInfo.charslot[0]=3;
					}

					ItemMG->RemoveItem(i);
					break;
				}

			}

			if (ItemMG->getVItem()[i]->GetItemIndex() == 6)
			{
				//아이템 먹었을때 효과 ( 손오공)
				//DATA->playerInfo.charslot[0] = 3;

				if (KEYMANAGER->isOnceKeyDown('F'))
				{

					if (DATA->playerInfo.charslot.size() < 2) DATA->playerInfo.charslot.push_back(3);
					else
					{

						if (DATA->playerInfo.charslot[0] == DATA->playerInfo.playertype)
						{
							ItemMG->set_CharBook((player->GetPlayerRC().right + player->GetPlayerRC().left) / 2,
								(player->GetPlayerRC().top + player->GetPlayerRC().bottom) / 2, DATA->playerInfo.charslot[0]);
							DATA->playerInfo.charslot[0] = 3;
						}
						else if (DATA->playerInfo.charslot[1] == DATA->playerInfo.playertype)
						{
							ItemMG->set_CharBook((player->GetPlayerRC().right + player->GetPlayerRC().left) / 2,
								(player->GetPlayerRC().top + player->GetPlayerRC().bottom) / 2, DATA->playerInfo.charslot[1]);
							DATA->playerInfo.charslot[1] = 3;
						}

						//DATA->playerInfo.charslot[0] = 3;
					}

					ItemMG->RemoveItem(i);
					break;
				}
			}

			//마지막아이템일때 승리씬으로 전환해주는곳 
			if (ItemMG->getVItem()[i]->GetItemIndex() == 14)
			{

				if (KEYMANAGER->isOnceKeyDown('F'))
				{
					SCENEMANAGER->changeScene("승리씬");
					ItemMG->RemoveItem(i);
					break;
				}

			}
		}
	}

}

void AllMap::GroundRectRender(int groundRECT)
{
	for (int i = 0; i < groundRECT; ++i)
	{
		Rectangle(CAMERAMANAGER->getWorldDC(), maprc[i].rc);
	}

}

void AllMap::LeftRectRender(int leftRECT)
{
	for (int i = 0; i < leftRECT; ++i)
	{
		Rectangle(CAMERAMANAGER->getWorldDC(), leftmaprc[i].rc);
	}
}

void AllMap::RightRectRender(int rightRECT)
{
	for (int i = 0; i < rightRECT; ++i)
	{
		Rectangle(CAMERAMANAGER->getWorldDC(), rightmaprc[i].rc);
	}
}

void AllMap::BuyItem()
{

	for (int i = 0; i < ItemMG->getVItem().size(); ++i)
	{
		if (ItemMG->getVItem().size() <= 0) return;
		RECT temp;
		if (IntersectRect(&temp, &player->GetPlayerRC(), &ItemMG->getVItem()[i]->GetItemRc()))
		{
			if (KEYMANAGER->isOnceKeyDown('F'))
			{

				//인데스 1 작은포션
				if (ItemMG->getVItem()[i]->GetItemIndex() == 1)
				{
					if (DATA->playerInfo.playerMoney >= ItemMG->getVItem()[i]->GetItemPrice())
					{
						DATA->playerInfo.playerMoney -= ItemMG->getVItem()[i]->GetItemPrice();

						DATA->playerInfo.playerHP += 30;
							ItemMG->RemoveItem(i);
							break;
						
					

					}
				}

				// 인덱스 2 큰포션
				if (ItemMG->getVItem()[i]->GetItemIndex() == 2)
				{
					if (DATA->playerInfo.playerMoney >= ItemMG->getVItem()[i]->GetItemPrice())
					{
						DATA->playerInfo.playerMoney -= ItemMG->getVItem()[i]->GetItemPrice();

						
							DATA->playerInfo.playerHP += 60;
							ItemMG->RemoveItem(i);
							break;
						
					

					}
				}

				//인덱스 7 투구
				if (ItemMG->getVItem()[i]->GetItemIndex() == 7)
				{
					if (DATA->playerInfo.playerMoney >= ItemMG->getVItem()[i]->GetItemPrice())
					{
						DATA->playerInfo.playerMoney -= ItemMG->getVItem()[i]->GetItemPrice();


						DATA->playerInfo.playerAMOR += 5;
						ItemMG->RemoveItem(i);
						break;

					

					}
				}

				//인덱스 8 방어구
				if (ItemMG->getVItem()[i]->GetItemIndex() == 8)
				{
					if (DATA->playerInfo.playerMoney >= ItemMG->getVItem()[i]->GetItemPrice())
					{
						DATA->playerInfo.playerMoney -= ItemMG->getVItem()[i]->GetItemPrice();


						DATA->playerInfo.playerAMOR += 10;
						ItemMG->RemoveItem(i);
						break;

					}
				}

				//인덱스 9 스피드 슈즈
				if (ItemMG->getVItem()[i]->GetItemIndex() == 9)
				{
					if (DATA->playerInfo.playerMoney >= ItemMG->getVItem()[i]->GetItemPrice())
					{
						DATA->playerInfo.playerMoney -= ItemMG->getVItem()[i]->GetItemPrice();


						DATA->playerInfo.playerSPEED += 3;
						ItemMG->RemoveItem(i);
						break;

					}
				}

				//인덱스 10 공격력검
				if (ItemMG->getVItem()[i]->GetItemIndex() == 10)
				{
					if (DATA->playerInfo.playerMoney >= ItemMG->getVItem()[i]->GetItemPrice())
					{
						DATA->playerInfo.playerMoney -= ItemMG->getVItem()[i]->GetItemPrice();


						DATA->playerInfo.playerPOWER += 5;
						ItemMG->RemoveItem(i);
						break;

					}
				}

				//인덱스 11 사거리검
				if (ItemMG->getVItem()[i]->GetItemIndex() == 11)
				{
					if (DATA->playerInfo.playerMoney >= ItemMG->getVItem()[i]->GetItemPrice())
					{
						DATA->playerInfo.playerMoney -= ItemMG->getVItem()[i]->GetItemPrice();


						DATA->playerInfo.playerATKRANGE += 10;
						ItemMG->RemoveItem(i);
						break;

					}
				}

				//인덱스 12 치명타장갑
				if (ItemMG->getVItem()[i]->GetItemIndex() == 12)
				{
					if (DATA->playerInfo.playerMoney >= ItemMG->getVItem()[i]->GetItemPrice())
					{
						DATA->playerInfo.playerMoney -= ItemMG->getVItem()[i]->GetItemPrice();


						DATA->playerInfo.playerCRITICAL += 10;
						ItemMG->RemoveItem(i);
						break;

					}
				}

				if (ItemMG->getVItem()[i]->GetItemIndex() == 13)
				{
					if (DATA->playerInfo.playerMoney >= ItemMG->getVItem()[i]->GetItemPrice())
					{
						DATA->playerInfo.playerMoney -= ItemMG->getVItem()[i]->GetItemPrice();


						DATA->playerInfo.isitem = true;
						ItemMG->RemoveItem(i);
						break;

					}
				}



			}
		}
	}
}


void AllMap::MakePotalCollison(string a)
{

	if (MonsterMG->getVmonster().size() <= 0)
	{
		currentpotalframe = 1;
		potal = RectMake(potalposX, potalposY, potalimg->getFrameWidth(), potalimg->getFrameHeight());
	}


	RECT temprc;

	if (IntersectRect(&temprc, &player->GetPlayerRC(), &potal)&& MonsterMG->getVmonster().size() <= 0)
	{
		istostring = true;
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			
			SCENEMANAGER->changeScene(a);
			
		}
	
		
	}
	else 
	{
		istostring = false;
	}

}

void AllMap::MakePotalCollison()
{
	if (MonsterMG->getVmonster().size() <= 0)
	{
		currentpotalframe = 1;
		potal = RectMake(potalposX, potalposY, potalimg->getFrameWidth(), potalimg->getFrameHeight());
	}


	RECT temprc;

	if (IntersectRect(&temprc, &player->GetPlayerRC(), &potal) && MonsterMG->getVmonster().size() <= 0)
	{
		istostring = true;
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			DATA->playerInfo.mapcount++;
			if (DATA->playerInfo.mapcount == 8)
			{
				SCENEMANAGER->changeScene("보스스테이지");
			}
			else if (DATA->playerInfo.mapcount == 3 || DATA->playerInfo.mapcount == 6)
			{
				SCENEMANAGER->changeScene("상점스테이지");
			}
			else
			{
				int rand = RND->getFromIntTo(1, 6);
				if (rand == 1)
					SCENEMANAGER->changeScene("스테이지1");
				else if (rand == 2)
					SCENEMANAGER->changeScene("스테이지2");
				else if (rand == 3)
					SCENEMANAGER->changeScene("스테이지3");
				else if (rand == 4)
					SCENEMANAGER->changeScene("스테이지4");
				else if (rand == 5)
					SCENEMANAGER->changeScene("스테이지5");
			}
		}


	}
	else
	{
		istostring = false;
	}
}

