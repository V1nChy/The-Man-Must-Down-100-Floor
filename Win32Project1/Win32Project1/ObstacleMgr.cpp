#include"ObstacleMgr.h"
#include"Game.h"

cObstacleMgr* cObstacleMgr::ObstacleMgr=NULL;
int cObstacleMgr::oTot = 0;
cObstacleMgr::cObstacleMgr()
{
	ObstacleMgr = this;

}
cObstacleMgr::~cObstacleMgr()
{
	
}
void cObstacleMgr::Enter()
{
	AddMovable(new cObstacle1(250, 150));
	AddMovable(new cObstacle2(400, 300));
	AddMovable(new cObstacle3(124, 450));
	AddMovable(new cObstacle1(175, 600));
	AddMovable(new cObstacle1(175, 750));
	oTot = 5;
	dis = 0;
}
void cObstacleMgr::Update(float deltaTime)
{
	list<cIMovable *>::iterator it = mMovableList.begin(), end = mMovableList.end(), temp;
	for (; it != end;)
	{
		temp = it;
		it++;
		cObstacle* obstacle = dynamic_cast<cObstacle*>(*temp);
		(*temp)->Update(deltaTime);
		if (obstacle->IfDelete())
		{
			delete (*temp);
			mMovableList.erase(temp);
		}
	}
	dis += GameScene::mGameSpeed*deltaTime;
	if (oTot < O1MAX && dis>150)
	{
		oTot++;
		dis = 0;
		int r = rand()%100;
		if (r<60)
			AddMovable(new cObstacle1(124+rand()%325, 800));
		else if (r<80)
			AddMovable(new cObstacle2(124 + rand() % 325, 800));
		else
			AddMovable(new cObstacle3(124 + rand() % 325, 800));
	}

}

cObstacleMgr* cObstacleMgr::GetpObstacleMgr()
{
	return ObstacleMgr;
}

list<cIMovable *>* cObstacleMgr::GetObstacleList()
{
	return &mMovableList;
}