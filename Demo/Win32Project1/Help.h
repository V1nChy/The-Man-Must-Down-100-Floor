#ifndef _HELP_H_
#define _HELP_H_

#include "GameFrame.h"
#include "Button.h"

class HelpScene :public Scene
{
	GameFrame* pGF;
	float mTtime;
	cImg* bg1, *bg2,*bg3;
public:

	void Init();
	void Enter();
	void Run(float deltaTime);
	void Quit();
};
#endif