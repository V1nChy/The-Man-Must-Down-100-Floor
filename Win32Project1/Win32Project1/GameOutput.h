#ifndef _GAME_OUTPUT_H_
#define _GAME_OUTPUT_H_

#include "BasicData.h"
#include "cImg.h"


class GameOutput
{
protected:
	int mClientW;
	int mClientH;
	HWND mhWnd;
	HDC mhDC;
	HDC mhMemDC;
	cImgManager mImgMap;
public:
	GameOutput(HWND hwnd);
	 ~GameOutput();

	void BeginOutput();
	void EndOutput();
	BOOL DrawText(TCHAR* temp, int x, int y);
	BOOL SetTitleText(TCHAR *title);

	cImg* LoadCximg(TCHAR* filename, const string ID, DWORD format);
	void DrawCximage(int x,int y,const string ID);


	int LoadDirectory(const TCHAR* DirectName, DWORD format);
	HDC GethMemDC(){ return mhMemDC; };
};
#endif