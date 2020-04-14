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
	_background = IMAGEMANAGER->addImage("로딩배경", "로딩씬.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("lodingfrontBar", "hpBarTop.bmp", WINSIZEX, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("lodingbackBar", "hpBarBottom.bmp", WINSIZEX, 50, true, RGB(255, 0, 255));
	_loadingBar = new progressBar;
	_loadingBar->init("loding",0, WINSIZEY - 50, WINSIZEX, 50);
	_loadingBar->setGauge(0, 0);

	CreateThread(
		NULL,			//스레드의 보안속성(자식윈도우가 있을때) 핸들로 자식인지 부모인지 파악
		NULL,			//스레드의 스택크기(NULL로 두면 메인쓰레드와 스택크기는 동일하다)
		threadFunction,	//스레드 사용할 함수 명
		this,			//스레드의 매개변수(this로하면 본 클래스)
		NULL,			//스레드의 특성(NULL로 두면 바로 실행한다)
		0				//스레드의 생성 후 스레드의 ID를 넘겨준다 보통은 NULL로 둠.
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
		SCENEMANAGER->changeScene("인스테이지");
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

		//■■■■■■■■■■■■■■■■■■■■■■■■■배경 ■■■■■■■■■■■■■■■■■■■■■
		//IMAGEMANAGER->addImage("인게임", "시작화면.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
		IMAGEMANAGER->addImage("tutorial_BG_0", "./resours/map/tutorial_BG_0.bmp", 2160, 1800, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("tutorial_BG_1", "./resours/map/tutorial_BG_1.bmp", 2160, 1800, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("tutorial_BG_2", "./resours/map/tutorial_BG_2.bmp", 2160, 1800, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("신룡1", "./resours/map/Dragon1.bmp", 15000, 900, 10, 1, false, RGB(0, 0, 0));
		IMAGEMANAGER->addFrameImage("신룡2", "./resours/map/Dragon2.bmp", 10500, 900, 7, 1, false, RGB(0, 0, 0));
		IMAGEMANAGER->addImage("배경2", "./resours/map/배경2.bmp", 2500, 2500, false, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("배경3", "./resours/map/배경3.bmp", 2160, 900, false, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("맑은하늘", "./resours/map/맑은하늘.bmp", 2000, 1400, false, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("검은하늘", "./resours/map/검은하늘.bmp", 2000, 1400, false, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("배경4", "./resours/map/배경4.bmp", 2000, 1400, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("배경5", "./resours/map/배경5.bmp", 4408, 900, true, RGB(255, 0, 255));
		//■■■■■■■■■■■■■■■■■■■■■■■■■맵 ■■■■■■■■■■■■■■■■■■■■■
		IMAGEMANAGER->addImage("인스테이지맵", "./resours/map/testMAP.bmp", 2160, 1800, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("스테이지1", "./resours/map/스테이지1.bmp", 2500, 2500, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("스테이지2", "./resours/map/스테이지2.bmp", 2000, 1400, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("스테이지3", "./resours/map/스테이지3.bmp", 3500, 1300, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("스테이지4", "./resours/map/스테이지4.bmp", 3500, 1300, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("스테이지5", "./resours/map/스테이지5.bmp", 2500, 1100, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("보스스테이지", "./resours/map/보스맵.bmp", 2500, 1200, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("상점스테이지", "./resours/map/상점스테이지(수정).bmp", 1800, 1000, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("캐릭터스테이지", "./resours/map/캐릭터스테이지.bmp", 2200, 1200, true, RGB(255, 0, 255));


		//미니맵 
		IMAGEMANAGER->addImage("미니맵1", "./resours/map/testMAP(미니).bmp", 270, 225, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("미니맵2", "./resours/map/스테이지1(미니).bmp", 313, 313, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("미니맵3", "./resours/map/스테이지2(미니).bmp", 250, 175, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("미니맵4", "./resours/map/스테이지3(미니).bmp", 438, 163, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("미니맵5", "./resours/map/스테이지4(미니).bmp", 438, 163, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("미니맵6", "./resours/map/스테이지5(미니).bmp", 313, 138, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("미니맵9", "./resours/map/보스맵(미니).bmp", 438, 150, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("미니맵7", "./resours/map/상점스테이지(수정)(미니).bmp", 225, 125, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("미니맵8", "./resours/map/캐릭터스테이지(미니).bmp", 275, 150, true, RGB(255, 0, 255));

		IMAGEMANAGER->addFrameImage("스테이지문", "./resours/map/스테이지문.bmp", 500, 303,2,1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("상점", "./resours/map/상점.bmp", 320, 173, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("상점돈", "./resours/map/상점돈.bmp", 30, 43, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("가시", "./resours/map/가시.bmp", 392, 80, true, RGB(255, 0, 255));

		IMAGEMANAGER->addImage("패배씬", "./resours/map/패배씬.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("승리씬", "./resours/map/승리씬.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
		//■■■■■■■■■■■■■■■■■■■■■■■■■플레이어 ■■■■■■■■■■■■■■■■■■■■■■■
		//IMAGEMANAGER->addImage("루피", "./resours/player/루피.bmp", 50, 120, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("기본캐릭터", "./resours/player/기본플레이어(수정).bmp", 1000, 1000, 8, 8, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("기본플레이어피격", "./resours/player/기본플레이어피격.bmp", 228, 218, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("나루토캐릭터", "./resours/player/나루토플레이어.bmp", 1000, 1000, 8, 8, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("루피캐릭터", "./resours/player/루피플레이어.bmp", 1000, 1000, 8, 8, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("손오공캐릭터", "./resours/player/손오공플레이어.bmp", 1000, 1000, 8, 8, true, RGB(255, 0, 255));



		//나루토
		IMAGEMANAGER->addFrameImage("나루토스킬1", "./resours/player/나루토스킬1.bmp", 760, 200, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("나루토아래공격", "./resours/player/나루토아래공격.bmp", 1309, 256, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("나루토위공격", "./resours/player/나루토위공격.bmp", 868, 310, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("나루토나선환", "./resours/player/나루토나선환.bmp", 2265, 266, 15, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("나루토변신", "./resours/player/나루토변신.bmp", 4400, 300, 20, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("나루토변신실패", "./resours/player/나루토변신실패.bmp", 1708 , 266, 14, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("나루토피격", "./resours/player/나루토피격.bmp", 294, 206, 3, 2, true, RGB(255, 0, 255));
		//루피
		IMAGEMANAGER->addFrameImage("루피위공격", "./resours/player/루피위공격.bmp", 1032, 520, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("루피아래공격", "./resours/player/루피아래공격.bmp", 2214, 214, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("루피난타", "./resours/player/루피난타.bmp", 2072, 250, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("루피바주카포", "./resours/player/루피바주카포.bmp", 3520, 222, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("루피스프링", "./resours/player/루피스프링.bmp", 1595, 360, 11, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("루피피격", "./resours/player/루피피격.bmp", 246, 216, 3, 2, true, RGB(255, 0, 255));
		//손오공
		IMAGEMANAGER->addFrameImage("손오공위공격", "./resours/player/손오공위공격.bmp", 822, 314, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("손오공아래공격", "./resours/player/손오공아래공격.bmp", 685, 314, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("손오공에너지파", "./resours/player/손오공에너지파.bmp", 1969, 282, 11, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("손오공원기옥", "./resours/player/손오공원기옥.bmp", 2086, 302, 14, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("손오공궁극기", "./resours/player/손오공궁극기.bmp", 940, 278, 10, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("손오공피격", "./resours/player/손오공피격.bmp", 327, 218, 3, 2, true, RGB(255, 0, 255));
		//■■■■■■■■■■■■■■■■■■■■■■■■■몬스터 ■■■■■■■■■■■■■■■■■■■■■■■
		IMAGEMANAGER->addFrameImage("몬스터1기본", "./resours/monster/몬스터1기본.bmp", 72, 178, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("몬스터1공격", "./resours/monster/몬스터1공격test.bmp", 417, 160, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("몬스터1이동", "./resours/monster/몬스터1이동test.bmp", 256, 190, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("몬스터1피격", "./resours/monster/몬스터1피격.bmp", 78, 208, 1, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("피콜로몬스터이동", "./resours/monster/피콜로몬스터이동.bmp", 450, 188, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("피콜로몬스터공격", "./resours/monster/피콜로몬스터공격.bmp", 498, 184, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("피콜로몬스터피격", "./resours/monster/피콜로몬스터피격.bmp", 158, 176, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("몬스터꽃", "./resours/monster/꽃공격.bmp", 375, 220, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("독꽃", "./resours/monster/독꽃.bmp", 168, 78, 3, 1, true, RGB(255, 0, 255));



		IMAGEMANAGER->addFrameImage("해적총알공격", "./resours/monster/해적총알공격.bmp", 1380, 244, 5, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("해적근접공격", "./resours/monster/해적근접공격.bmp", 2008, 244, 8, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("해군대장이동", "./resours/monster/해군대장이동1.bmp", 600, 222, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("해군대장공격", "./resours/monster/해군대장공격1.bmp", 806, 222, 6, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("해군대장피격", "./resours/monster/해군대장피격.bmp", 320, 229, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("아카츠키몬스터점멸", "./resours/monster/아카츠키몬스터점멸1.bmp", 263, 250, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("아카츠키몬스터피격", "./resours/monster/아카츠키몬스터피격.bmp", 120, 168, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("상점주인", "./resours/monster/상점주인.bmp", 600, 161, 4, 1, true, RGB(255, 0, 255));
		
		IMAGEMANAGER->addFrameImage("보스기본", "./resours/monster/보스기본.bmp", 2231, 400, 6, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("보스공격", "./resours/monster/보스공격.bmp", 5256, 577, 9, 1, true, RGB(255, 0, 255));
		
		IMAGEMANAGER->addFrameImage("하얀수염이미지", "./resours/monster/하얀수염.bmp", 1385, 710, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("에넬이미지", "./resours/monster/에넬.bmp", 1190, 404, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("미호크이미지", "./resours/monster/미호크.bmp", 1230, 508, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("스모크이미지", "./resours/monster/스모크.bmp", 648, 195, 3, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("우솝이미지", "./resours/monster/우솝.bmp", 3000, 300, 10, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("빈몬스터", "./resours/monster/nullmonster.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));

		//■■■■■■■■■■■■■■■■■■■■■■■■■총알 ■■■■■■■■■■■■■■■■■■■■■■■
		IMAGEMANAGER->addFrameImage("몬스터꽃총알", "./resours/bullet/몬스터총알1.bmp", 152, 60, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("피콜로총알", "./resours/bullet/피콜로총알.bmp", 80, 37, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("해적총알", "./resours/bullet/해적총알.bmp", 150, 150, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("새총알", "./resours/bullet/새총알.bmp", 82, 56, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("수리검", "./resours/bullet/수리검.bmp", 150, 56, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("아이템총알", "./resours/bullet/아이템총알.bmp", 65, 66, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("보스총알", "./resours/bullet/우솝총알.bmp", 60, 60, 2, 2, true, RGB(255, 0, 255));
		//■■■■■■■■■■■■■■■■■■■■■■■■■이펙트 ■■■■■■■■■■■■■■■■■■■■■■■
		IMAGEMANAGER->addImage("오른쪽경로이펙트", "./resours/effect/오른쪽투사체경로.bmp", 143, 120, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("왼쪽경로이펙트", "./resours/effect/왼쪽투사체경로.bmp", 143, 120, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("독이펙트1", "./resours/effect/독이펙트1.bmp", 810, 112, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("해적이펙트", "./resours/effect/해적이펙트2.bmp", 1200, 168, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("해군이펙트", "./resours/effect/해군이펙트.bmp", 1560, 73, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("에너지파오른쪽", "./resours/effect/에너지파오른쪽.bmp", 1500, 249, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("에너지파왼쪽", "./resours/effect/에너지파왼쪽.bmp", 1500, 249, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("원기옥", "./resours/effect/원기옥.bmp", 4108, 500, 8, 1, true, RGB(255, 0, 255)); //0.19
		

		//■■■■■■■■■■■■■■■■■■■■■■■■■UI ■■■■■■■■■■■■■■■■■■■■■■■
		IMAGEMANAGER->addImage("오타쿠이미지", "./resours/ui/아톰이미지.bmp", 100, 100, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("나루토이미지", "./resours/ui/나루토이미지.bmp", 100, 100, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("루피이미지", "./resours/ui/루피이미지.bmp", 100, 100, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("손오공이미지", "./resours/ui/손오공이미지.bmp", 100, 100, true, RGB(255, 0, 255));

		IMAGEMANAGER->addImage("초기작은이미지", "./resours/ui/초기작은이미지.bmp", 60, 60, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("오타쿠작은이미지", "./resours/ui/아톰작은이미지.bmp", 60, 60, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("나루토작은이미지", "./resours/ui/나루토작은이미지.bmp", 60, 60, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("루피작은이미지", "./resours/ui/루피작은이미지.bmp", 60, 60, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("손오공작은이미지", "./resours/ui/손오공작은이미지.bmp", 60, 60, true, RGB(255, 0, 255));

		IMAGEMANAGER->addImage("skillslot", "./resours/ui/기본skillslot.bmp", 278, 72, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("나루토skillslot", "./resours/ui/나루토skillslot.bmp", 278, 72, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("루피skillslot", "./resours/ui/루피skillslot.bmp", 278, 72, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("손오공skillslot", "./resours/ui/손오공skillslot.bmp", 278, 72, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("돈모양", "./resours/ui/돈모양.bmp", 40, 57, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("플레이어정보창", "./resours/ui/플레이어정보.bmp", 148, 241, true, RGB(255, 0, 255));
		char num[20];
		char load[50];
		for (int i = 0; i < 10; i++) {
			sprintf_s(num, "%d", i);
			sprintf_s(load, "./resours/ui/%d.bmp", i);
			IMAGEMANAGER->addImage(num, load, 23, 30, true, RGB(255, 0, 255));
		}
		//■■■■■■■■■■■■■■■■■■■■■■■■■Item ■■■■■■■■■■■■■■■■■■■■■■■
		IMAGEMANAGER->addFrameImage("돈", "./resours/item/money.bmp", 85, 30, 4, 1, true, RGB(255, 0, 255)); 
		IMAGEMANAGER->addFrameImage("작은포션", "./resours/item/작은포션.bmp", 30, 36, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("큰포션", "./resours/item/큰포션.bmp", 40, 43, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("나루토책", "./resours/item/나루토책.bmp", 191, 45, 4, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("원피스책", "./resours/item/원피스책.bmp", 191, 45, 4, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("드래곤볼책", "./resours/item/드래곤볼책.bmp", 191, 45, 4, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("공격력검", "./resours/item/공격력검.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("사거리검", "./resours/item/사거리검.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("모자", "./resours/item/모자.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("방어구", "./resours/item/방어구.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("신발", "./resours/item/신발.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("장갑", "./resours/item/장갑.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("구슬", "./resours/item/구슬.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("마지막책", "./resours/item/마지막책.bmp", 100, 108, 1, 1, true, RGB(255, 0, 255));


		//■■■■■■■■■■■■■■■■■■■■■■■■■사운드 ■■■■■■■■■■■■■■■■■■■■■■■
		SOUNDMANAGER->addSound("배경음악", "./resours/audio/stageMusic.mp3", true, true);
		SOUNDMANAGER->addSound("맞았을때", "./resours/audio/맞았을때.wav", true, false);
		SOUNDMANAGER->addSound("일반공격", "./resours/audio/일반공격.wav", true, false);
		SOUNDMANAGER->addSound("스킬공격", "./resours/audio/스킬공격.wav", true, false);
		SOUNDMANAGER->addSound("던질때", "./resours/audio/표창소리.wav", true, false);
		SOUNDMANAGER->addSound("피격", "./resours/audio/피격.wav", true, false);
		SOUNDMANAGER->addSound("나선환", "./resours/audio/나선환.wav", true, false);
		SOUNDMANAGER->addSound("나루토괴물", "./resours/audio/나루토괴물.wav", true, false);
		SOUNDMANAGER->addSound("원기옥", "./resours/audio/원기옥.wav", true, false);
		SOUNDMANAGER->addSound("루피바주카포", "./resours/audio/루피바주카포.wav", true, false);
		SOUNDMANAGER->addSound("동전", "./resours/audio/동전.wav", true, false);
		SOUNDMANAGER->addSound("물먹는소리", "./resours/audio/물먹는소리.mp3", true, false);

		//보스스테이지
		SOUNDMANAGER->addSound("보스맵음악", "./resours/audio/보스맵음악.mp3", true, true);
		SOUNDMANAGER->addSound("에넬전기소리", "./resours/audio/에넬전기.wav", true, false);

		SOUNDMANAGER->addSound("미호크검소리", "./resours/audio/미호크검소리.wav", true, false);
		SOUNDMANAGER->addSound("하얀수염지진", "./resours/audio/지진.wav", true, false);

		SOUNDMANAGER->addSound("스모크연기", "./resours/audio/스모크연기.wav", true, false);
		//Sleep(1);



		loadHealper->_currentCount++;

	}
	return 0;
}
