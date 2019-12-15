#include"Obstacle2.h"
#include"GameFrame.h"
#include"ObstacleMgr.h"

cObstacle2::cObstacle2(float x, float y) :
cObstacle(x, y, 0, 0, 0)
{
	SetImg(GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\ci.png", "ci.png", CXIMAGE_FORMAT_PNG));
}
cObstacle2::~cObstacle2()
{}
RECT cObstacle2::GetRect()
{
	RECT r;
	r.left = mPos.x - mWidth / 2;
	r.top = mPos.y;
	r.right = mPos.x + mWidth / 2;
	r.bottom = mPos.y + mHeight / 2;
	return r;
}
