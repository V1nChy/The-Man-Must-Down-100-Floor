#include"Obstacle1.h"
#include"GameFrame.h"

cObstacle1::cObstacle1(float x, float y) :
cObstacle(x, y, 0, 0, 0)
{
	SetImg(GameFrame::GetObject()->GetGO()->LoadCximg(L"img\\plate1.png", "plate1.png", CXIMAGE_FORMAT_PNG));
}
cObstacle1::~cObstacle1()
{}
