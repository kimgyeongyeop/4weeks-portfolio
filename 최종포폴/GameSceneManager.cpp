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
	SCENEMANAGER->addScene("��ŸƮ��", new StarteScene);
	SCENEMANAGER->addScene("�ε���", new loadingScene);
	SCENEMANAGER->addScene("�ν�������", new InStage);
	SCENEMANAGER->addScene("��������1", new Stage1);
	SCENEMANAGER->addScene("��������2", new Stage2);
	SCENEMANAGER->addScene("��������3", new Stage3);
	SCENEMANAGER->addScene("��������4", new Stage4);
	SCENEMANAGER->addScene("��������5", new Stage5);
	SCENEMANAGER->addScene("������������", new ShopStage);
	SCENEMANAGER->addScene("ĳ���ͽ�������", new CharacterStage);
	SCENEMANAGER->addScene("������������", new BossMap);
	SCENEMANAGER->addScene("�¸���", new Victory);
	SCENEMANAGER->addScene("�й��", new Lose);
#pragma endregion 
	SCENEMANAGER->changeScene("��ŸƮ��");

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
