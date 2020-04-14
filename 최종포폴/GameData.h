#pragma once
#include <vector>
struct PlayerInfo
{
	POINT currentplayerPos;

	float locationX, locationY;
	int playerHP;
	int playertype;
	int initX;
	int initO;
	float skill1cooltime;
	float skill2cooltime;
	float skill3cooltime;
	float skill4cooltime;
	int playerMoney;
	int Killnum;
	int playerPOWER;
	int playerATKRANGE;
	int playerAMOR;
	int playerSPEED;
	int playerCRITICAL;
	bool isitem ;
	int playtime;
	int mapcount;
	//int		charslot[2];
	vector<int> charslot{ 0 };
	//int charslot[2];

	int currentmapindex;

	PlayerInfo()
	{
		currentplayerPos = { 0,0 };
		mapcount = 0;
		playtime = 0;
		Killnum = 0;
		playerHP = 200;
		playerPOWER = 1;
		playerAMOR = 1;
		playerSPEED = 1;
		playertype = 0;
		playerATKRANGE = 1;
		locationX = 770;

		locationY = 1530;
		initX = 0;
		initO = 0;
		skill1cooltime = 0;
		skill2cooltime = 0;
		skill3cooltime = 0;
		skill4cooltime = 0;
		playerMoney = 0;
		playerCRITICAL = 10;
		isitem = false;
		currentmapindex = 0;
		//charslot[0]=0;
		//charslot[0]=0;
		//charslot[0] = 0;
		
	}
};
class GameData
{
	public:
		PlayerInfo playerInfo;

		GameData();
		~GameData();
	};



