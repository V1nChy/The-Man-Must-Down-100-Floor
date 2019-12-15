#ifndef _GAME_INPUT_
#define _GAME_INPUT_

#include"BasicData.h"

class GameInput
{
public:
	GameInput();
	~GameInput();
	BOOL mESC;
	BOOL mSPACE;
	BOOL mF5;

	BOOL mLEFT;
	BOOL mRIGHT;

	void Enter();
	void Run(float t);
};

#endif