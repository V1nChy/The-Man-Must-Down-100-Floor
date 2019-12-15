#ifndef _MENU_H_
#define _MENU_H_

#include "GameFrame.h"
#include "Button.h"

class MenuScene :public Scene
{
	GameFrame* pGF;
	float mTime;
	cImg* bg1, *bg2;
public:

	void Init();
	void Enter();
	void Run(float deltaTime);
	void Quit();
};
#endif