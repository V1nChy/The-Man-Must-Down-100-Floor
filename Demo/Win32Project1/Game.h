#ifndef _GAME_H_
#define _GAME_H_

#include "GameFrame.h"
#include "Button.h"
#include "Background.h"
#include "Role.h"
#include "ObstacleMgr.h"

class GameScene :public Scene
{
	float mTime;
	GameFrame* pGF;
	HDC mhDC;

	cRole* mRole;
	cObstacleMgr* ObstacleMgr;
	cBackground* mBg;

	BOOL mEnd;
public:
	static float mGameSpeed;
	void Init();
	void Enter();
	void Run(float deltaTime);
	void Quit();
	void End();
};
#endif