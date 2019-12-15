#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include"GameFrame.h"
#include"Basicdata.h"
#include<stack>

class cBackground
{
	GameFrame* pGF;
	float mTime;
	int bw1, bh1;
	int bw2, bh2;
	float mBg1_y;

	HDC mBorderDC;
	HDC mLifeDC;
	cImg* TopCi;
	cImg* bg1, *bg2;
	cImg* mLife_bg,*mScore_bg;
	cImg** mNum;
	cImg* mEnd;
	cImg* mReadr, *mGo;

	stack<int> score;
public:
	cBackground(HDC hdc);
	~cBackground();

	void Enter();
	void Update(float deltaTime);
	void Draw(HDC hdc);
	void Draw2(HDC hdc);
	void Draw3(HDC hdc);
	void DrawReady(HDC hdc);
	void DrawGo(HDC hdc);
	void EndDraw(HDC hdc);

};

#endif