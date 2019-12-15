#ifndef _OBSTACLE2_H_
#define _OBSTACLE2_H_


#include"Obstacle.h"

class cObstacle2 :public cObstacle
{

public:
	cObstacle2(float x, float y);
	~cObstacle2();
	RECT GetRect();
};

#endif