#include"Obstacle3.h"
#include"GameFrame.h"
#include"Game.h"

cObstacle3::cObstacle3(float x, float y) :
cObstacle(x, y, 0, 0, 0)
{
	mImg = new cImg*[5];
	mImg[0] = GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\plate3.png", "plate3.png", CXIMAGE_FORMAT_PNG);
	mImg[1] = GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\plate4.png", "plate4.png", CXIMAGE_FORMAT_PNG);
	mImg[2] = GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\plate5.png", "plate5.png", CXIMAGE_FORMAT_PNG);
	mImg[3] = GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\plate6.png", "plate6.png", CXIMAGE_FORMAT_PNG);
	mImg[4] = GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\plate2.png", "plate2.png", CXIMAGE_FORMAT_PNG);
	OutputStrategy* p1 = new OutputStrategy(0, 4, 0.1);
	mOutputStrategy["ห้"] = p1;

	OutputStrategy* p2 = new OutputStrategy(4, 5, 1);
	mOutputStrategy["ีýณฃ"] = p2;

	m_pOutputStrategy = p2;
	mCount = 4;
}
cObstacle3::~cObstacle3()
{
	delete mImg;
}
void cObstacle3::Update(float deltaTime)
{

	mCount = m_pOutputStrategy->Update(deltaTime);
	mWidth = mImg[mCount]->GetWidth();
	mHeight = mImg[mCount]->GetHeight();

	mPos.y -= GameScene::mGameSpeed * deltaTime;
	if (mPos.y < 0)
	{
		mExist.AnimationEnd = TRUE;
		mExist.Die = TRUE;
	}
	if (mExist.Die && m_pOutputStrategy->GetIfOnePeriod())
	{
		mExist.AnimationEnd = TRUE;
	}
}
void cObstacle3::Draw(HDC hdc)
{
	mImg[mCount]->Draw(hdc,mPos.x,mPos.y);
}
void cObstacle3::SetDie()
{
	m_pOutputStrategy = mOutputStrategy["ห้"];
	mExist.Die = TRUE;
}