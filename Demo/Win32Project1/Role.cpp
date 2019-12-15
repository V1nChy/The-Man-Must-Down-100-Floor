#include"Role.h"
#include"GameFrame.h"
#include"ObstacleMgr.h"
#include"Game.h"

int cRole::mHP=0;
int cRole::mScore=0;
cRole::cRole(int x, int y, int vx, int hp) :
cIMovable(x, y, vx, 0)
{
	mHP = hp;
	mImg = new cImg*[9];
	mImg[0] = GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\stand.png","stand.png",CXIMAGE_FORMAT_PNG);
	mImg[1] = GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\left1.png", "left1.png", CXIMAGE_FORMAT_PNG);
	mImg[2] = GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\left2.png", "left2.png", CXIMAGE_FORMAT_PNG);
	mImg[3] = GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\left3.png", "left3.png", CXIMAGE_FORMAT_PNG);
	mImg[4] = GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\right1.png", "right1.png", CXIMAGE_FORMAT_PNG);
	mImg[5] = GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\right2.png", "right2.png", CXIMAGE_FORMAT_PNG);
	mImg[6] = GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\right3.png", "right3.png", CXIMAGE_FORMAT_PNG);
	mImg[7] = GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\jump1.png", "jump1.png", CXIMAGE_FORMAT_PNG);
	mImg[8] = GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\jump2.png", "jump2.png", CXIMAGE_FORMAT_PNG);

	OutputStrategy* p1 = new OutputStrategy(0, 1, 1);
	mOutputStrategy["’æ¡¢"] = p1;

	OutputStrategy* p2 = new OutputStrategy(1, 4, 0.08);
	mOutputStrategy["◊Û≈‹"] = p2;

	OutputStrategy* p3 = new OutputStrategy(4, 7, 0.08);
	mOutputStrategy["”“≈‹"] = p3;

	OutputStrategy* p4 = new OutputStrategy(7, 9, 0.1);
	mOutputStrategy["Ã¯"] = p4;

	mState = "’æ¡¢";
	m_pOutputStrategy = p1;

	mDirect.y = 1;
	mFrame = 9;
	mCount = 0;
	mWidth = mImg[mCount]->GetWidth();
	mHeight = mImg[mCount]->GetHeight();
}
cRole::~cRole()
{
	delete mImg;

	map<string, OutputStrategy*>::iterator i;
	for (i = mOutputStrategy.begin(); i != mOutputStrategy.end(); i++)
		delete i->second;
	mOutputStrategy.clear();
}
void cRole::Enter()
{
	mState = "’æ¡¢";
	SetOutputStrategy(mState);
	mCount = 0;

	mExist.AnimationEnd = FALSE;
	mExist.Die = FALSE;

	mHP = 190;
	mScore = 0;
	mPos.x = 120;
	mPos.y = 200;
	ySpeed = 20;
	last = now = NULL;
	mSignHurt = NULL;
}
void cRole::Update(float deltaTime)
{
	Move(deltaTime);
	SetState();

	if (now!=last)
	{
		last = now;
		mScore++;
		mHP += 2;
		if (mHP > 190)
			mHP = 190;
		if (dynamic_cast<cObstacle1*>(last))
			Scene::sound.play(ON);
		if (dynamic_cast<cObstacle2*>(last))
			Scene::sound.play(HURT);
		if (dynamic_cast<cObstacle3*>(last))
			Scene::sound.play(FLIPON);
	}
	if (mPos.y<116 + mHeight / 2)
	{
		Bleed(5);
	}
	if (mPos.y > 710)
	{
		mExist.AnimationEnd = TRUE;
		mExist.Die = TRUE;
		Scene::sound.play(DIE);
	}

	mCount=m_pOutputStrategy->Update(deltaTime);
	mWidth = mImg[mCount]->GetWidth();
	mHeight = mImg[mCount]->GetHeight();
}

void cRole::Draw(HDC hdc)
{
	mImg[mCount]->Draw(hdc,mPos.x,mPos.y);
}

void cRole::Move(float deltaTime)
{
	mDirect.x = 0;
	if (GameFrame::GetObject()->GetGI()->mRIGHT)
		mDirect.x += 1;
	if (GameFrame::GetObject()->GetGI()->mLEFT)
		mDirect.x -= 1;
	int xdis = mDirect.x*GameScene::mGameSpeed*deltaTime*1.2;
	if (xdis != 0)
	{
		RECT rx;
		if (xdis > 0)
		{
			rx.top = mPos.y - mHeight / 2;
			rx.left = mPos.x;
			rx.bottom = mPos.y + mHeight / 2-5;
			rx.right = mPos.x + mWidth / 2 + xdis-10;
		}
		else if (xdis < 0)
		{
			rx.top = mPos.y - mHeight / 2;
			rx.left = mPos.x - mWidth / 2 - xdis+10;
			rx.bottom = mPos.y + mHeight / 2-5;
			rx.right = mPos.x;
		}

		if (!CollisionDetectX(cObstacleMgr::GetpObstacleMgr()->GetObstacleList(), rx))
			mPos.x += xdis;
	}
	if (mPos.x > 509 - mWidth / 2)
		mPos.x = 509 - mWidth / 2;
	if (mPos.x<64+mWidth/2)
		mPos.x = 64+mWidth / 2;

	ySpeed += GRAVITY*deltaTime * 60;
	int ydis = mDirect.y*ySpeed*deltaTime;
	RECT ry;
	ry.top = mPos.y;
	ry.left = mPos.x - mWidth / 2+10;
	ry.bottom = ry.top + mHeight / 2 + ydis;
	ry.right = mPos.x + mWidth / 2-10;
	if (!CollisionDetectY(cObstacleMgr::GetpObstacleMgr()->GetObstacleList(), ry))
		mPos.y += ydis;
}
void cRole::SetState()
{
	string nowS;
	if (mDirect.x == 1)
		nowS = "”“≈‹";
	else if (mDirect.x == -1)
		nowS = "◊Û≈‹";
	else
		nowS = "’æ¡¢";

	if (mDirect.y == 1)
		nowS = "Ã¯";

	if (mState != nowS)
	{
		mState = nowS;
		SetOutputStrategy(mState);
	}

}

void cRole::SetOutputStrategy(const string ID)
{
	map<string, OutputStrategy*>::iterator i = mOutputStrategy.find(ID);
	if (i == mOutputStrategy.end())
		return;
	m_pOutputStrategy = i->second;
	m_pOutputStrategy->Enter();
}

void cRole::Bleed(int power)
{
	if (mHP == 0)
		return;
	mHP -= power;
	if (mHP <= 0)
	{
		mHP == 0;
		mExist.AnimationEnd = TRUE;
		mExist.Die = TRUE;
		Scene::sound.play(DIE);
	}
}

BOOL cRole::CollisionDetectY(list<cIMovable *>* plist, RECT moveR)
{
	RECT r;
	list<cIMovable *>::iterator itr1 = plist->begin(), end1 = plist->end(), temp;
	while (itr1 != end1)
	{
		temp = itr1++;
		cObstacle* obstacle = dynamic_cast<cObstacle*>(*temp);
		RECT obstacleR = obstacle->GetRect();
		if (!obstacle->IfDie() && IntersectRect(&r, &moveR, &obstacleR))
		{
			if (dynamic_cast<cObstacle2*>(*temp))
			{
				Bleed(1);
			}
			if (dynamic_cast<cObstacle3*>(*temp))
			{
				(dynamic_cast<cObstacle3*>(*temp))->SetDie();
			}
			mPos.y = obstacleR.top - mHeight / 2;
			now = obstacle;
			mDirect.y = 0;
			ySpeed = 20;
			return TRUE;
		}
	}
	mDirect.y = 1;
	return FALSE;
}
BOOL cRole::CollisionDetectX(list<cIMovable *>* plist, RECT moveR)
{
	RECT r;
	list<cIMovable *>::iterator itr1 = plist->begin(), end1 = plist->end(), temp;
	while (itr1 != end1)
	{
		temp = itr1++;
		cObstacle* obstacle = dynamic_cast<cObstacle*>(*temp);
		RECT obstacleR = obstacle->GetRect();
		if (!obstacle->IfDie() && IntersectRect(&r, &moveR, &obstacleR))
		{
			return TRUE;
		}
	}
	return FALSE;

}