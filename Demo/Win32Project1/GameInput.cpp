#include"GameInput.h"
#include"Gameframe.h"
GameInput::GameInput() :
mESC(FALSE),
mSPACE(FALSE),
mF5(FALSE),
mLEFT(FALSE),
mRIGHT(FALSE)
{
}
GameInput::~GameInput()
{}
void GameInput::Enter()
{
}
void GameInput::Run(float t)
{
	mSPACE = GetAsyncKeyState(VK_SPACE) & 0X8000;
	if (GameFrame::GetObject()->GetIsRun())
		return;
	mESC = GetAsyncKeyState(VK_ESCAPE) & 0X8000;
	mF5 = GetAsyncKeyState(VK_F5) & 0X8000;

	mLEFT = GetAsyncKeyState(VK_LEFT) & 0X8000;
	mRIGHT = GetAsyncKeyState(VK_RIGHT) & 0X8000;
}