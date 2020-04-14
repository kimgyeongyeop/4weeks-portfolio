#pragma once
#include "gameNode.h"
#include "StarteScene.h"
#include "loadingScene.h"
#include "InStage.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Stage5.h"
#include "ShopStage.h"
#include "CharacterStage.h"
#include "BossMap.h"
#include "Victory.h"
#include "Lose.h"
class GameSceneManager : public gameNode
{
public:
	GameSceneManager();
	~GameSceneManager();

	HRESULT init();
	void release();
	void update();
	void render();
};

