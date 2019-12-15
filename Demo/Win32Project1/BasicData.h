#ifndef _GONGXIANG_H_
#define _GONGXIANG_H_

#include <windows.h>
#include <tchar.h>
#include <math.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <io.h>
#include <stdlib.h>
using namespace std;

#define ClientW 573
#define ClientH 693

#define MAXNAMELEN 20

#define GRAVITY 10

#define O1MAX 5



//������ʼ��
#define _YL_ 0.5f

//	��Ч�ı��
#define GAME_MAIN 1
#define HURT      2
#define ON        3
#define DIE       4
#define BUTTON    5
#define READYGO   6
#define FLIPON        7
struct sEXIST
{
	BOOL Die;
	BOOL AnimationEnd;
};
struct sDirect
{
	int x;
	int y;
};


class cPOINTF
{
public:
	float x;
	float y;
	float angle;	// ����һȦ2PI

	float GetDistance(cPOINTF & s);
	float GetAngle(cPOINTF & d);
};
BOOL RestrictInBoundary(RECT r);
#endif