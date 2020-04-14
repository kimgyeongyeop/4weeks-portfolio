#include "stdafx.h"
#include "GameSceneManager.h"


GameSceneManager::GameSceneManager()
{
}


GameSceneManager::~GameSceneManager()
{
}

HRESULT GameSceneManager::init()
{

	gameNode::init(true);

#pragma region Scene
	SCENEMANAGER->addScene("스타트씬", new StarteScene);
	SCENEMANAGER->addScene("로딩씬", new loadingScene);
	SCENEMANAGER->addScene("인스테이지", new InStage);
	SCENEMANAGER->addScene("스테이지1", new Stage1);
	SCENEMANAGER->addScene("스테이지2", new Stage2);
	SCENEMANAGER->addScene("스테이지3", new Stage3);
	SCENEMANAGER->addScene("스테이지4", new Stage4);
	SCENEMANAGER->addScene("스테이지5", new Stage5);
	SCENEMANAGER->addScene("상점스테이지", new ShopStage);
	SCENEMANAGER->addScene("캐릭터스테이지", new CharacterStage);
	SCENEMANAGER->addScene("보스스테이지", new BossMap);
	SCENEMANAGER->addScene("승리씬", new Victory);
	SCENEMANAGER->addScene("패배씬", new Lose);
#pragma endregion 
	SCENEMANAGER->changeScene("스타트씬");

	return S_OK;
}

void GameSceneManager::release()
{
	gameNode::release();

	
}

void GameSceneManager::update()
{
	gameNode::update();

	SCENEMANAGER->update();
}

void GameSceneManager::render()
{
	SCENEMANAGER->render();
}
