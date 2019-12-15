#ifndef _ROLE_H_
#define _ROLE_H_

#include "Obstacle.h"
#include "Strategy.h"

class cRole :public cIMovable
{
	map<string, OutputStrategy*> mOutputStrategy;
	OutputStrategy* m_pOutputStrategy;

	cImg** mImg;
	int mFrame;
	int mCount;

	string mState;

	cObstacle* last, *now;
	BOOL mSignHurt;
public:
	static int mHP;
	static int mScore;
	cRole(int x,int y,int vx,int hp);
	~cRole();
	void Enter();
	void Update(float deltaTime);
	void Draw(HDC hdc);

	void Move(float deltaTime);
	void SetState();
	void SetOutputStrategy(const string ID);
	void Bleed(int power);

	BOOL CollisionDetectY(list<cIMovable *>* plist,RECT moveR);
	BOOL CollisionDetectX(list<cIMovable *>* plist, RECT moveR);
};

#endif