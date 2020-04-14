#include "stdafx.h"
#include "Boss.h"


Boss::Boss()
{
}


Boss::~Boss()
{
}

HRESULT Boss::init(POINT pos)
{
	
	SOUNDMANAGER->play("보스맵음악", 1.0f);
	monsterindex = 8;
	monsterinfo.pos = pos;
	monsterinfo.currentFrameX = 0;
	monsterinfo.currentFrameY = 0;
	
	RL = false;
	playercheak = false;
	bulletfire = false;
	monsterinfo.rc = RectMake(monsterinfo.pos.x, monsterinfo.pos.y + 5, 400, 400);
	monsterinfo.img = IMAGEMANAGER->findImage("보스기본");
	IMAGEMANAGER->addImage("bossfrontBar", "hpBarTop.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossbackBar", "hpBarBottom.bmp", monsterinfo.rc.right - monsterinfo.rc.left, 10, true, RGB(255, 0, 255));
	monsterhpBar = new progressBar;
	monsterhpBar->init("boss", monsterinfo.rc.left, monsterinfo.rc.top - 20, monsterinfo.rc.right - monsterinfo.rc.left, 10);
	monstercurrentHP = monstermaxHP = 5000;
	count = 0;
	states.insert(make_pair("기본", new Idle(this)));
	states.insert(make_pair("미호크", new Skill1(this)));
	states.insert(make_pair("에넬", new Skill2(this)));
	states.insert(make_pair("하얀수염", new Skill3(this)));
	states.insert(make_pair("우솝", new Skill4(this)));
	states.insert(make_pair("스모크", new Skill5(this)));
	ChangeState("기본");
	errorX = 0;
	errorY = 0;
	skillintervel=0;
	skillcount = 0;
	isendskill = false;
	isstartskill = false;
	skillimg = IMAGEMANAGER->findImage("미호크이미지");
	isstoremonster = true;
	monsterinfo.atkRC = RectMakeCenter(monsterinfo.pos.x , monsterinfo.pos.y , 0, 0);
	EFFECTMANAGER->addEffect("보스연막", "./resours/effect/보스연막.bmp", 653, 200, 163, 200, 1.f, 0.3f, 5); //0.5
	EFFECTMANAGER->addEffect("스모그연막", "./resours/effect/스모그연막.bmp", 2286, 700, 571, 700, 1.f, 0.07f, 100); //0.5
	EFFECTMANAGER->addEffect("하얀수염폭발", "./resours/effect/explosion.bmp", 1200, 89, 50, 89, 1.f, 1.2f, 100); //26장
	EFFECTMANAGER->addEffect("에넬전기", "./resours/effect/에넬전기.bmp", 1325, 200, 189, 200, 1.f, 0.2f, 20); 
	EFFECTMANAGER->addEffect("에넬전기발사", "./resours/effect/에넬전기발사.bmp", 1000, 300, 111, 300, 1.f, 0.2f, 20);
	
	skillposx = skillposy = 0;
	Inskillintervel = 0;
	bossplayerposX = bossplayerposY = 0;
	tempplayerposx = tempplayerposy = 0;
	
	return S_OK;
}

void Boss::release()
{
}

void Boss::update()
{
	
	//cout << isstoremonster << endl;
	

	monsterhpBar->setGauge(monstercurrentHP, monstermaxHP);

	if (currentState) // 값이 있으면 업데이트 시켜라.
		currentState->Update();

	prograssbar();
	frame();
	//prograssbar();
	
	skillintervel++;

	
	if (skillintervel > 300)
	{
		isstartskill = true;
		skillintervel = 0;
	}

	if (isstartskill)
	{

		random = RND->getFromIntTo(1, 6);

		
		switch (random)
		{
		case 1:
			ChangeState("미호크");
			break;
		case 2:
			ChangeState("에넬");
			break;
		case 3:
			ChangeState("하얀수염");
			break;
		case 4:
			ChangeState("우솝");
			break;
		case 5:
			ChangeState("스모크");
			break;
			
		}
	}


	monsterinfo.rc = RectMake(monsterinfo.pos.x, monsterinfo.pos.y + 5, 400, 400);
}

void Boss::render()
{
	monsterinfo.img->frameRender(CAMERAMANAGER->getWorldDC(), monsterinfo.pos.x+errorX, monsterinfo.pos.y + errorY, monsterinfo.currentFrameX, monsterinfo.currentFrameY);
	if(!isstartskill)
	skillimg->frameRender(CAMERAMANAGER->getWorldDC(), skillposx, skillposy, skillframecurenntX, skillframecurenntY);

	Monster::render();
	

}

void Boss::frame()
{
	count++;
	if (count % 15 == 0)
	{
		monsterinfo.currentFrameX++;
		count = 0;
	}
	if (monsterinfo.currentFrameX >= monsterinfo.img->getMaxFrameX()) {

		monsterinfo.currentFrameX = 0;

	}

	if (monsterinfo.img == IMAGEMANAGER->findImage("보스기본"))
	{
		errorX = 0;
		errorY = 0;
	}
	else if (monsterinfo.img == IMAGEMANAGER->findImage("보스공격"))
	{
		errorX = -100;
		errorY = -130;
	}


	








}

void Boss::prograssbar()
{
	monsterhpBar->update();
	monsterhpBar->setX(monsterinfo.rc.left);
	monsterhpBar->setY(monsterinfo.rc.top - 50);
}



void Boss::ChangeState(string key)
{
	StateBase* state = states[key];
	state->Enter();
	currentState = state;
}


void Idle::Enter()
{
	me->Inskillintervel = 0;
	me->monsterinfo.img = IMAGEMANAGER->findImage("보스기본");
	me->monsterinfo.atkRC = RectMakeCenter(me->monsterinfo.pos.x, me->monsterinfo.pos.y, 0, 0);
	me->bulletfire = false;
	me->skillimg = IMAGEMANAGER->findImage("빈몬스터");
}

void Idle::Update()
{

}

void Skill1::Enter()
{
	me->skillposx = me->bossplayerposX-200;
	me->skillposy = me->bossplayerposY-200;

	me->isstartskill = false;
	me->monsterinfo.img = IMAGEMANAGER->findImage("보스공격");
	me->skillimg = IMAGEMANAGER->findImage("미호크이미지");
	me->skillcount = 0;

	
		me->skillframecurenntX = 0;
		me->skillframecurenntY = 0;
	


	EFFECTMANAGER->play("보스연막", me->skillposx + me->skillimg->getFrameWidth() / 2, me->skillposy + me->skillimg->getFrameHeight() / 2);
	
}

void Skill1::Update()
{

	me->Inskillintervel++;


	if (me->Inskillintervel >= 20)
	{

		me->skillcount++;


		

			if (me->skillcount % 10 == 0)
			{
				me->skillframecurenntX++;
				me->skillcount = 0;
			}
			if (me->skillframecurenntX >= me->skillimg->getMaxFrameX())
			{

				me->ChangeState("기본");

			}
		
			if (me->skillcount % 3 == 0 && me->skillframecurenntX==3 )
			{
				SOUNDMANAGER->play("미호크검소리", 1.0f);
				me->monsterinfo.atkRC = RectMake(me->skillposx, me->skillposy, 300, 200);
			}

	}

}


void Skill2::Enter()
{
	
	me->skillposx = 1300;
	me->skillposy = 500;
	me->isstartskill = false;
	me->monsterinfo.img = IMAGEMANAGER->findImage("보스공격");
	me->skillimg = IMAGEMANAGER->findImage("에넬이미지");
	me->skillcount = 0;
	me->skillframecurenntX = 0;
	me->skillframecurenntY = 0;
	EFFECTMANAGER->play("보스연막", me->skillposx + me->skillimg->getFrameWidth() / 2, me->skillposy + me->skillimg->getFrameHeight() / 2);
}

void Skill2::Update()
{
	me->Inskillintervel++;
	

	if (me->Inskillintervel >= 20)
	{
		
		

		

		me->skillcount++;
		if (me->skillcount % 15 == 0)
		{
			
			me->skillframecurenntX++;
			me->skillcount = 0;
		}

		if (me->skillcount == 1 )
		{
			SOUNDMANAGER->play("에넬전기소리", 1.0f);
			//me->monsterinfo.atkRC = RectMakeCenter(me->monsterinfo.pos.x, me->monsterinfo.pos.y, 0, 0);
			EFFECTMANAGER->play("에넬전기", me->bossplayerposX,
				me->bossplayerposY - 300);
			me->tempplayerposx = me->bossplayerposX;
			me->tempplayerposy = me->bossplayerposY;
		}

		if (me->skillcount == 8)
		{
			EFFECTMANAGER->play("에넬전기발사", me->bossplayerposX,
				me->bossplayerposY - 100);
			me->monsterinfo.atkRC = RectMakeCenter(me->tempplayerposx, me->tempplayerposy, 40, 300);
		}
		
		

		if (me->skillframecurenntX >= me->skillimg->getMaxFrameX() ) {

			me->ChangeState("기본");

		}

	}

}


void Skill3::Enter()
{
	me->skillposx = 1300;
	me->skillposy = 500;
	me->isstartskill = false;
	me->monsterinfo.img = IMAGEMANAGER->findImage("보스공격");
	me->skillimg = IMAGEMANAGER->findImage("하얀수염이미지");
	me->skillcount = 0;
	me->skillframecurenntX = me->skillimg->getMaxFrameX()-1;
	me->skillframecurenntY = 1;
	EFFECTMANAGER->play("보스연막", me->skillposx+ me->skillimg->getFrameWidth() / 2, me->skillposy + me->skillimg->getFrameHeight()/2);
}

void Skill3::Update()
{

	
	me->Inskillintervel++;

	if (me->Inskillintervel >= 30)
	{
		
		me->skillcount++;




		if (me->skillcount % 10 == 0)
		{
			
			me->skillframecurenntX--;
			me->skillcount = 0;
		}
		if (me->skillframecurenntX <0) {

			me->ChangeState("기본");

		}

		if(me->skillframecurenntX ==1 && me->skillcount == 8)
		me->monsterinfo.atkRC = RectMake(0, 800 , me->monsterinfo.pos.x + 600, 100);
		SOUNDMANAGER->play("하얀수염지진", 1.0f);

		EFFECTMANAGER->play("하얀수염폭발", RND->getFromIntTo(0, me->monsterinfo.pos.x+500),
			850);
		CAMERAMANAGER->Strong_Camera_WorldDC_Shake();





	}

}


void Skill4::Enter()
{
	
	me->skillposx = 1000;
	me->skillposy = 600;
	me->isstartskill = false;
	me->monsterinfo.img = IMAGEMANAGER->findImage("보스공격");
	me->skillimg = IMAGEMANAGER->findImage("우솝이미지");
	me->skillcount = 0;
	me->skillframecurenntX = 0;
	me->skillframecurenntY = 0;
	EFFECTMANAGER->play("보스연막", me->skillposx + me->skillimg->getFrameWidth() / 2, me->skillposy + me->skillimg->getFrameHeight() / 2);
}

void Skill4::Update()
{

	
	me->Inskillintervel++;

	if (me->Inskillintervel >= 50)
	{


		me->skillcount++;

		if (me->skillcount % 8 == 0)
		{
			me->skillframecurenntX++;

			me->skillcount = 0;
		}

		if (me->skillcount == 1 || me->skillcount == 3 || me->skillcount == 5 || me->skillcount == 7)
		{

			me->bulletfire = true;
		}
		else
		{
			me->bulletfire = false;
		}


		if (me->skillframecurenntX >= me->skillimg->getMaxFrameX())
		{

			me->ChangeState("기본");

		}


	}
}


void Skill5::Enter()
{
	
	me->skillposx = 1300;
	me->skillposy = 600;
	me->isstartskill = false;
	me->monsterinfo.img = IMAGEMANAGER->findImage("보스공격");
	me->skillimg = IMAGEMANAGER->findImage("스모크이미지");
	me->skillcount = 0;
	me->skillframecurenntX = 0;
	me->skillframecurenntY = 0;
	EFFECTMANAGER->play("보스연막", me->skillposx + me->skillimg->getFrameWidth() / 2, me->skillposy + me->skillimg->getFrameHeight() / 2);
	
}

void Skill5::Update()
{


	me->Inskillintervel++;

	if (me->Inskillintervel >= 30)
	{
		me->skillcount++;



		if (me->skillcount % 12 == 0)
		{
			me->skillframecurenntX++;
			me->skillcount = 0;
		}

		if (me->skillframecurenntX == 2 && me->skillcount >= 0 && me->skillcount <= 5)
		{
			SOUNDMANAGER->play("스모크연기", 1.0f);
			EFFECTMANAGER->play("스모그연막", RND->getFromIntTo(me->monsterinfo.pos.x - 200, me->monsterinfo.pos.x + 500),
				RND->getFromIntTo(me->monsterinfo.pos.y, me->monsterinfo.pos.y + 200));
		}

		me->monsterinfo.atkRC = RectMakeCenter(me->monsterinfo.pos.x + 170, me->monsterinfo.pos.y + 200, 900, 600);



		if (me->skillframecurenntX >= me->skillimg->getMaxFrameX()) {

			me->ChangeState("기본");

		}
	}
}

