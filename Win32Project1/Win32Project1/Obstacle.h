#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "IMovable.h"

class cObstacle :public cIMovable
{
	int mPower;
public:
	cObstacle(float x, float y, float vx, float vy,int power);
	~cObstacle();

	void Update(float deltaTime);
	int GetPower(){ return mPower; };
	BOOL IfDelete();
	BOOL IfDie();
};

#endif