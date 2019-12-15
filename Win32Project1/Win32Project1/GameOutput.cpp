#include"GameOutput.h"
#include <io.h>
#include <stdlib.h>
#pragma comment(lib, "Msimg32.lib")

GameOutput::GameOutput(HWND hwnd):
mhWnd(hwnd),
mhDC(0),
mhMemDC(0),
mClientH(0),
mClientW(0)
{
	RECT r;
	GetClientRect(mhWnd, &r);
	mClientW = r.right - r.left;
	mClientH = r.bottom - r.top;

	mhDC = GetDC(mhWnd);

	HBITMAP hbmp;
	mhMemDC = CreateCompatibleDC(mhDC);
	hbmp = CreateCompatibleBitmap(mhDC, mClientW, mClientH);
	DeleteObject(SelectObject(mhMemDC, hbmp));
	DeleteObject(hbmp);

	SetTextColor(mhMemDC,RGB(255,255,255));
	SetBkMode(mhMemDC, TRANSPARENT);
}
GameOutput::~GameOutput()
{
	//mImgMap.ClearAll();

	DeleteDC(mhMemDC);
	ReleaseDC(mhWnd, mhDC);
}
void GameOutput::BeginOutput()
{

	BitBlt(mhMemDC, 0, 0, mClientW, mClientH, 0, 0, 0, BLACKNESS);
}
void GameOutput::EndOutput()
{
	BitBlt(mhDC, 0, 0, mClientW, mClientH, mhMemDC, 0, 0, SRCCOPY);
}

cImg* GameOutput::LoadCximg(TCHAR* filename, const string ID, DWORD format)
{
	return mImgMap.CreateImg(filename, ID, format);
}

void GameOutput::DrawCximage(int x,int y,const string ID)
{
	mImgMap.SetImg(ID)->Draw(mhMemDC,x,y);
}
BOOL GameOutput::DrawText(TCHAR* temp,int x,int y)
{
	TextOut(mhMemDC, x, y, temp, _tcslen(temp));
	return TRUE;
}
BOOL GameOutput::SetTitleText(TCHAR *title)
{
	return 0 != SetWindowText(mhWnd, title);
}

int GameOutput::LoadDirectory(const TCHAR* DirectName, DWORD format)
{
	char cname[260];
	TCHAR tname[260];
	wcstombs(cname, DirectName, wcslen(DirectName) + 1);

	char dir[260];
	strcpy_s(dir, 260, cname);
	strcat_s(dir, 260, "\\*");
	int r = 0;

	_finddata_t fd;
	intptr_t fr = _findfirst(dir, &fd);

	if (-1 != fr)
	{
		int go = 0;
		while (!go)
		{
			if ((fd.attrib & _A_SUBDIR))
			{
				if (strcmp(fd.name, ".") != 0 && strcmp(fd.name, "..") != 0)
				{
					strcpy_s(dir, 260, cname);
					strcat_s(dir, 260, "\\");
					strcat_s(dir, 260, fd.name);
					r += LoadDirectory((TCHAR*)dir, format);
				}
			}
			else
			{
				strcpy_s(dir, 260, cname);
				strcat_s(dir, 260, "\\");
				strcat_s(dir, 260, fd.name);

				mbstowcs(tname, dir, strlen(dir) + 1);

				r += LoadCximg(tname, fd.name, format) ? 1 : 0;
			}
			go = _findnext(fr, &fd);
		}
	}

	return r;
}