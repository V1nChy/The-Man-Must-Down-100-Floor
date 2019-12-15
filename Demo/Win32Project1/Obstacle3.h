#ifndef _OBSTACLE3_H_
#define _OBSTACLE3_H_

#include"Obstacle.h"
#include "Strategy.h"

class cObstacle3 :public cObstacle
{
	cImg** mImg;
	map<string, OutputStrategy*> mOutputStrategy;
	OutputStrategy* m_pOutputStrategy;
	int mCount;
public:
	cObstacle3(float x, float y);
	~cObstacle3();
	void Update(float deltaTime);
	void Draw(HDC hdc);
	void SetDie();
};

#endif