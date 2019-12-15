#include"GameFrame.h"
#include"Menu.h"
#include"Game.h"
#include"Help.h"
#include<tchar.h>

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdSow)
{
	GameFrame* pGF = GameFrame::GetObject();
	pGF->LoadScene(new MenuScene, "Menu场景");
	pGF->LoadScene(new GameScene, "Game场景");
	pGF->LoadScene(new HelpScene, "Help场景");
	pGF->SetScene("Menu场景");
	pGF->Run();
	pGF->End();
	return 1;
}