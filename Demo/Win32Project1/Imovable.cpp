#include "IMovable.h"

cIMovable::cIMovable()
{}
cIMovable::cIMovable(float x, float y, float vx, float vy)
{
	xSpeed = vx;
	ySpeed = vy;
	mWidth = 0.0f;
	mHeight = 0.0f;
	mPos.x = x;
	mPos.y = y;
	mPos.angle = 0;

	mDirect.x = 0;
	mDirect.y = 0;

	mExist.AnimationEnd = FALSE;
	mExist.Die = FALSE;

	mImg = NULL;
}


cIMovable::~cIMovable()
{
}


void cIMovable::Update(float deltaTime)
{
	mPos.x += xSpeed * deltaTime;
	mPos.y += ySpeed * deltaTime;
}


void cIMovable::Draw(HDC hdc)
{
	mImg->Draw(hdc, mPos.x, mPos.y, mPos.angle);
}


cPOINTF cIMovable::GetPos()
{
	return mPos;
}


RECT cIMovable::GetRect()
{
	RECT r;
	r.left = mPos.x - mWidth / 2;
	r.top = mPos.y - mHeight / 2;
	r.right = mPos.x + mWidth / 2;
	r.bottom = mPos.y + mHeight / 2;
	return r;
}


void cIMovable::SetImg(cImg* img)
{
	mImg = img;
	mWidth = img->GetWidth();
	mHeight = img->GetHeight();
}
BOOL cIMovable::GetIfDie()
{
	if (mExist.AnimationEnd && mExist.Die)
	{
		return TRUE;
	}
	return FALSE;
}
