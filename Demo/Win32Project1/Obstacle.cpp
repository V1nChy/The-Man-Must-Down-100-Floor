#include"Obstacle.h"
#include"Game.h"
#include"ObstacleMgr.h"

cObstacle::cObstacle(float x, float y, float vx, float vy, int power) :
cIMovable(x, y, vx, vy),
mPower(power)
{
}
cObstacle::~cObstacle()
{}
void cObstacle::Update(float deltaTime)
{
	mPos.y -= GameScene::mGameSpeed * deltaTime;
	if (mPos.y < 0)
	{
		mExist.AnimationEnd = TRUE;
		mExist.Die = TRUE;
	}
}
BOOL cObstacle::IfDelete()
{
	if (mExist.AnimationEnd && mExist.Die)
	{
		cObstacleMgr::oTot--;
		return TRUE;
	}
	return FALSE;
}
BOOL cObstacle::IfDie()
{
	return mExist.Die;
}