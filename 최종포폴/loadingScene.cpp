#include "stdafx.h"
#include "loadingScene.h"
#include "progressBar.h"

loadingScene::loadingScene()
	: _background(nullptr), _loadingBar(nullptr),
	_currentCount(0)
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	_background = IMAGEMANAGER->addImage("�ε����", "�ε���.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("lodingfrontBar", "hpBarTop.bmp", WINSIZEX, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("lodingbackBar", "hpBarBottom.bmp", WINSIZEX, 50, true, RGB(255, 0, 255));
	_loadingBar = new progressBar;
	_loadingBar->init("loding",0, WINSIZEY - 50, WINSIZEX, 50);
	_loadingBar->setGauge(0, 0);

	CreateThread(
		NULL,			//�������� ���ȼӼ�(�ڽ������찡 ������) �ڵ�� �ڽ����� �θ����� �ľ�
		NULL,			//�������� ����ũ��(NULL�� �θ� ���ξ������ ����ũ��� �����ϴ�)
		threadFunction,	//������ ����� �Լ� ��
		this,			//�������� �Ű�����(this���ϸ� �� Ŭ����)
		NULL,			//�������� Ư��(NULL�� �θ� �ٷ� �����Ѵ�)
		0				//�������� ���� �� �������� ID�� �Ѱ��ش� ������ NULL�� ��.
	);

	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loadingBar);
	//SAFE_DELETE(_background);
	
}

void loadingScene::update()
{
	_loadingBar->update();
	_loadingBar->setGauge(_currentCount, LOADINGMAX);

	if (_currentCount == LOADINGMAX)
	{
		SCENEMANAGER->changeScene("�ν�������");
	}

}

void loadingScene::render()
{
	_background->render(getMemDC(), 0, 0);
	_loadingBar->render(getMemDC());
}

DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	loadingScene* loadHealper = (loadingScene*)lpParameter;

	while (loadHealper->_currentCount != LOADINGMAX)
	{

		//���������������������������� ����������������������
		//IMAGEMANAGER->addImage("�ΰ���", "����ȭ��.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
		IMAGEMANAGER->addImage("tutorial_BG_0", "./resours/map/tutorial_BG_0.bmp", 2160, 1800, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("tutorial_BG_1", "./resours/map/tutorial_BG_1.bmp", 2160, 1800, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("tutorial_BG_2", "./resours/map/tutorial_BG_2.bmp", 2160, 1800, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�ŷ�1", "./resours/map/Dragon1.bmp", 15000, 900, 10, 1, false, RGB(0, 0, 0));
		IMAGEMANAGER->addFrameImage("�ŷ�2", "./resours/map/Dragon2.bmp", 10500, 900, 7, 1, false, RGB(0, 0, 0));
		IMAGEMANAGER->addImage("���2", "./resours/map/���2.bmp", 2500, 2500, false, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("���3", "./resours/map/���3.bmp", 2160, 900, false, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�����ϴ�", "./resours/map/�����ϴ�.bmp", 2000, 1400, false, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�����ϴ�", "./resours/map/�����ϴ�.bmp", 2000, 1400, false, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("���4", "./resours/map/���4.bmp", 2000, 1400, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("���5", "./resours/map/���5.bmp", 4408, 900, true, RGB(255, 0, 255));
		//��������������������������� ����������������������
		IMAGEMANAGER->addImage("�ν���������", "./resours/map/testMAP.bmp", 2160, 1800, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("��������1", "./resours/map/��������1.bmp", 2500, 2500, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("��������2", "./resours/map/��������2.bmp", 2000, 1400, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("��������3", "./resours/map/��������3.bmp", 3500, 1300, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("��������4", "./resours/map/��������4.bmp", 3500, 1300, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("��������5", "./resours/map/��������5.bmp", 2500, 1100, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("������������", "./resours/map/������.bmp", 2500, 1200, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("������������", "./resours/map/������������(����).bmp", 1800, 1000, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("ĳ���ͽ�������", "./resours/map/ĳ���ͽ�������.bmp", 2200, 1200, true, RGB(255, 0, 255));


		//�̴ϸ� 
		IMAGEMANAGER->addImage("�̴ϸ�1", "./resours/map/testMAP(�̴�).bmp", 270, 225, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�̴ϸ�2", "./resours/map/��������1(�̴�).bmp", 313, 313, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�̴ϸ�3", "./resours/map/��������2(�̴�).bmp", 250, 175, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�̴ϸ�4", "./resours/map/��������3(�̴�).bmp", 438, 163, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�̴ϸ�5", "./resours/map/��������4(�̴�).bmp", 438, 163, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�̴ϸ�6", "./resours/map/��������5(�̴�).bmp", 313, 138, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�̴ϸ�9", "./resours/map/������(�̴�).bmp", 438, 150, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�̴ϸ�7", "./resours/map/������������(����)(�̴�).bmp", 225, 125, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�̴ϸ�8", "./resours/map/ĳ���ͽ�������(�̴�).bmp", 275, 150, true, RGB(255, 0, 255));

		IMAGEMANAGER->addFrameImage("����������", "./resours/map/����������.bmp", 500, 303,2,1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("����", "./resours/map/����.bmp", 320, 173, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("������", "./resours/map/������.bmp", 30, 43, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("����", "./resours/map/����.bmp", 392, 80, true, RGB(255, 0, 255));

		IMAGEMANAGER->addImage("�й��", "./resours/map/�й��.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�¸���", "./resours/map/�¸���.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
		//���������������������������÷��̾� ������������������������
		//IMAGEMANAGER->addImage("����", "./resours/player/����.bmp", 50, 120, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�⺻ĳ����", "./resours/player/�⺻�÷��̾�(����).bmp", 1000, 1000, 8, 8, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�⺻�÷��̾��ǰ�", "./resours/player/�⺻�÷��̾��ǰ�.bmp", 228, 218, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("������ĳ����", "./resours/player/�������÷��̾�.bmp", 1000, 1000, 8, 8, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("����ĳ����", "./resours/player/�����÷��̾�.bmp", 1000, 1000, 8, 8, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�տ���ĳ����", "./resours/player/�տ����÷��̾�.bmp", 1000, 1000, 8, 8, true, RGB(255, 0, 255));



		//������
		IMAGEMANAGER->addFrameImage("�����佺ų1", "./resours/player/�����佺ų1.bmp", 760, 200, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("������Ʒ�����", "./resours/player/������Ʒ�����.bmp", 1309, 256, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("������������", "./resours/player/������������.bmp", 868, 310, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�����䳪��ȯ", "./resours/player/�����䳪��ȯ.bmp", 2265, 266, 15, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�����亯��", "./resours/player/�����亯��.bmp", 4400, 300, 20, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�����亯�Ž���", "./resours/player/�����亯�Ž���.bmp", 1708 , 266, 14, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�������ǰ�", "./resours/player/�������ǰ�.bmp", 294, 206, 3, 2, true, RGB(255, 0, 255));
		//����
		IMAGEMANAGER->addFrameImage("����������", "./resours/player/����������.bmp", 1032, 520, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("���ǾƷ�����", "./resours/player/���ǾƷ�����.bmp", 2214, 214, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("���ǳ�Ÿ", "./resours/player/���ǳ�Ÿ.bmp", 2072, 250, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("���ǹ���ī��", "./resours/player/���ǹ���ī��.bmp", 3520, 222, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("���ǽ�����", "./resours/player/���ǽ�����.bmp", 1595, 360, 11, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�����ǰ�", "./resours/player/�����ǰ�.bmp", 246, 216, 3, 2, true, RGB(255, 0, 255));
		//�տ���
		IMAGEMANAGER->addFrameImage("�տ���������", "./resours/player/�տ���������.bmp", 822, 314, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�տ����Ʒ�����", "./resours/player/�տ����Ʒ�����.bmp", 685, 314, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�տ�����������", "./resours/player/�տ�����������.bmp", 1969, 282, 11, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�տ��������", "./resours/player/�տ��������.bmp", 2086, 302, 14, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�տ����ñر�", "./resours/player/�տ����ñر�.bmp", 940, 278, 10, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�տ����ǰ�", "./resours/player/�տ����ǰ�.bmp", 327, 218, 3, 2, true, RGB(255, 0, 255));
		//����������������������������� ������������������������
		IMAGEMANAGER->addFrameImage("����1�⺻", "./resours/monster/����1�⺻.bmp", 72, 178, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("����1����", "./resours/monster/����1����test.bmp", 417, 160, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("����1�̵�", "./resours/monster/����1�̵�test.bmp", 256, 190, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("����1�ǰ�", "./resours/monster/����1�ǰ�.bmp", 78, 208, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("���ݷθ����̵�", "./resours/monster/���ݷθ����̵�.bmp", 450, 188, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("���ݷθ��Ͱ���", "./resours/monster/���ݷθ��Ͱ���.bmp", 498, 184, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("���ݷθ����ǰ�", "./resours/monster/���ݷθ����ǰ�.bmp", 158, 176, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("���Ͳ�", "./resours/monster/�ɰ���.bmp", 375, 220, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("����", "./resours/monster/����.bmp", 168, 78, 3, 1, true, RGB(255, 0, 255));



		IMAGEMANAGER->addFrameImage("�����Ѿ˰���", "./resours/monster/�����Ѿ˰���.bmp", 1380, 244, 5, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("������������", "./resours/monster/������������.bmp", 2008, 244, 8, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�ر������̵�", "./resours/monster/�ر������̵�1.bmp", 600, 222, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�ر��������", "./resours/monster/�ر��������1.bmp", 806, 222, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�ر������ǰ�", "./resours/monster/�ر������ǰ�.bmp", 320, 229, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("��ī��Ű��������", "./resours/monster/��ī��Ű��������1.bmp", 263, 250, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("��ī��Ű�����ǰ�", "./resours/monster/��ī��Ű�����ǰ�.bmp", 120, 168, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("��������", "./resours/monster/��������.bmp", 600, 161, 4, 1, true, RGB(255, 0, 255));
		
		IMAGEMANAGER->addFrameImage("�����⺻", "./resours/monster/�����⺻.bmp", 2231, 400, 6, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("��������", "./resours/monster/��������.bmp", 5256, 577, 9, 1, true, RGB(255, 0, 255));
		
		IMAGEMANAGER->addFrameImage("�Ͼ�����̹���", "./resours/monster/�Ͼ����.bmp", 1385, 710, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�����̹���", "./resours/monster/����.bmp", 1190, 404, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("��ȣũ�̹���", "./resours/monster/��ȣũ.bmp", 1230, 508, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("����ũ�̹���", "./resours/monster/����ũ.bmp", 648, 195, 3, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("����̹���", "./resours/monster/���.bmp", 3000, 300, 10, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�����", "./resours/monster/nullmonster.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));

		//���������������������������Ѿ� ������������������������
		IMAGEMANAGER->addFrameImage("���Ͳ��Ѿ�", "./resours/bullet/�����Ѿ�1.bmp", 152, 60, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("���ݷ��Ѿ�", "./resours/bullet/���ݷ��Ѿ�.bmp", 80, 37, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�����Ѿ�", "./resours/bullet/�����Ѿ�.bmp", 150, 150, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("���Ѿ�", "./resours/bullet/���Ѿ�.bmp", 82, 56, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("������", "./resours/bullet/������.bmp", 150, 56, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�������Ѿ�", "./resours/bullet/�������Ѿ�.bmp", 65, 66, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�����Ѿ�", "./resours/bullet/����Ѿ�.bmp", 60, 60, 2, 2, true, RGB(255, 0, 255));
		//������������������������������Ʈ ������������������������
		IMAGEMANAGER->addImage("�����ʰ������Ʈ", "./resours/effect/����������ü���.bmp", 143, 120, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("���ʰ������Ʈ", "./resours/effect/��������ü���.bmp", 143, 120, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("������Ʈ1", "./resours/effect/������Ʈ1.bmp", 810, 112, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("��������Ʈ", "./resours/effect/��������Ʈ2.bmp", 1200, 168, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�ر�����Ʈ", "./resours/effect/�ر�����Ʈ.bmp", 1560, 73, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�������Ŀ�����", "./resours/effect/�������Ŀ�����.bmp", 1500, 249, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�������Ŀ���", "./resours/effect/�������Ŀ���.bmp", 1500, 249, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�����", "./resours/effect/�����.bmp", 4108, 500, 8, 1, true, RGB(255, 0, 255)); //0.19
		

		//��������������������������UI ������������������������
		IMAGEMANAGER->addImage("��Ÿ���̹���", "./resours/ui/�����̹���.bmp", 100, 100, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�������̹���", "./resours/ui/�������̹���.bmp", 100, 100, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�����̹���", "./resours/ui/�����̹���.bmp", 100, 100, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�տ����̹���", "./resours/ui/�տ����̹���.bmp", 100, 100, true, RGB(255, 0, 255));

		IMAGEMANAGER->addImage("�ʱ������̹���", "./resours/ui/�ʱ������̹���.bmp", 60, 60, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("��Ÿ�������̹���", "./resours/ui/���������̹���.bmp", 60, 60, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�����������̹���", "./resours/ui/�����������̹���.bmp", 60, 60, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("���������̹���", "./resours/ui/���������̹���.bmp", 60, 60, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�տ��������̹���", "./resours/ui/�տ��������̹���.bmp", 60, 60, true, RGB(255, 0, 255));

		IMAGEMANAGER->addImage("skillslot", "./resours/ui/�⺻skillslot.bmp", 278, 72, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("������skillslot", "./resours/ui/������skillslot.bmp", 278, 72, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("����skillslot", "./resours/ui/����skillslot.bmp", 278, 72, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�տ���skillslot", "./resours/ui/�տ���skillslot.bmp", 278, 72, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�����", "./resours/ui/�����.bmp", 40, 57, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("�÷��̾�����â", "./resours/ui/�÷��̾�����.bmp", 148, 241, true, RGB(255, 0, 255));
		char num[20];
		char load[50];
		for (int i = 0; i < 10; i++) {
			sprintf_s(num, "%d", i);
			sprintf_s(load, "./resours/ui/%d.bmp", i);
			IMAGEMANAGER->addImage(num, load, 23, 30, true, RGB(255, 0, 255));
		}
		//��������������������������Item ������������������������
		IMAGEMANAGER->addFrameImage("��", "./resours/item/money.bmp", 85, 30, 4, 1, true, RGB(255, 0, 255)); 
		IMAGEMANAGER->addFrameImage("��������", "./resours/item/��������.bmp", 30, 36, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("ū����", "./resours/item/ū����.bmp", 40, 43, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("������å", "./resours/item/������å.bmp", 191, 45, 4, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("���ǽ�å", "./resours/item/���ǽ�å.bmp", 191, 45, 4, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�巡�ﺼå", "./resours/item/�巡�ﺼå.bmp", 191, 45, 4, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("���ݷ°�", "./resours/item/���ݷ°�.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("��Ÿ���", "./resours/item/��Ÿ���.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("����", "./resours/item/����.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("��", "./resours/item/��.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�Ź�", "./resours/item/�Ź�.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("�尩", "./resours/item/�尩.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("����", "./resours/item/����.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("������å", "./resours/item/������å.bmp", 100, 108, 1, 1, true, RGB(255, 0, 255));


		//����������������������������� ������������������������
		SOUNDMANAGER->addSound("�������", "./resours/audio/stageMusic.mp3", true, true);
		SOUNDMANAGER->addSound("�¾�����", "./resours/audio/�¾�����.wav", true, false);
		SOUNDMANAGER->addSound("�Ϲݰ���", "./resours/audio/�Ϲݰ���.wav", true, false);
		SOUNDMANAGER->addSound("��ų����", "./resours/audio/��ų����.wav", true, false);
		SOUNDMANAGER->addSound("������", "./resours/audio/ǥâ�Ҹ�.wav", true, false);
		SOUNDMANAGER->addSound("�ǰ�", "./resours/audio/�ǰ�.wav", true, false);
		SOUNDMANAGER->addSound("����ȯ", "./resours/audio/����ȯ.wav", true, false);
		SOUNDMANAGER->addSound("�����䱫��", "./resours/audio/�����䱫��.wav", true, false);
		SOUNDMANAGER->addSound("�����", "./resours/audio/�����.wav", true, false);
		SOUNDMANAGER->addSound("���ǹ���ī��", "./resours/audio/���ǹ���ī��.wav", true, false);
		SOUNDMANAGER->addSound("����", "./resours/audio/����.wav", true, false);
		SOUNDMANAGER->addSound("���Դ¼Ҹ�", "./resours/audio/���Դ¼Ҹ�.mp3", true, false);

		//������������
		SOUNDMANAGER->addSound("����������", "./resours/audio/����������.mp3", true, true);
		SOUNDMANAGER->addSound("��������Ҹ�", "./resours/audio/��������.wav", true, false);

		SOUNDMANAGER->addSound("��ȣũ�˼Ҹ�", "./resours/audio/��ȣũ�˼Ҹ�.wav", true, false);
		SOUNDMANAGER->addSound("�Ͼ��������", "./resours/audio/����.wav", true, false);

		SOUNDMANAGER->addSound("����ũ����", "./resours/audio/����ũ����.wav", true, false);
		//Sleep(1);



		loadHealper->_currentCount++;

	}
	return 0;
}
