#ifndef _OBSTACLEMGR_H_
#define _OBSTACLEMGR_H_

#include "ImovableMgr.h"
#include"Obstacle.h"
#include"Obstacle1.h"
#include"Obstacle2.h"
#include"Obstacle3.h"

class cObstacleMgr :public cMovableMgr
{
	static cObstacleMgr* ObstacleMgr;
	float dis;
public:
	static int oTot;
	cObstacleMgr();
	~cObstacleMgr();
	void Update(float deltaTime);
	void Enter();
	static cObstacleMgr* GetpObstacleMgr();
	list<cIMovable *>* GetObstacleList();

};


#endif