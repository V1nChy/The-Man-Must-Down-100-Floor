#include"GameFrame.h"
#include"Menu.h"
#include"Game.h"
#include"Help.h"
#include<tchar.h>

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdSow)
{
	GameFrame* pGF = GameFrame::GetObject();
	pGF->LoadScene(new MenuScene, "Menu����");
	pGF->LoadScene(new GameScene, "Game����");
	pGF->LoadScene(new HelpScene, "Help����");
	pGF->SetScene("Menu����");
	pGF->Run();
	pGF->End();
	return 1;
}