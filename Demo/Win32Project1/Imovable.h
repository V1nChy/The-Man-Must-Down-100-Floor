#ifndef _IMOVABLE_H_
#define _IMOVABLE_H_

#include "BasicData.h"
#include "cImg.h"

class cIMovable
{
protected:
	cPOINTF mPos;
	sDirect mDirect;
	sEXIST mExist;
	float xSpeed;
	float ySpeed;

	cImg* mImg;
	float mWidth;
	float mHeight;
public:
	cIMovable();
	cIMovable(float x, float y, float vx, float vy);
	~cIMovable();
	virtual void Update(float deltaTime);
	virtual void Draw(HDC hdc);
	cPOINTF GetPos();
	virtual RECT GetRect();
	void SetImg(cImg* img);
	BOOL GetIfDie();
};
#endif

