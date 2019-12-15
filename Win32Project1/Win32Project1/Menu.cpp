#include"Menu.h"

void MenuScene::Init()
{
	pGF = GameFrame::GetObject();
	mTime = 0;

	bg1=pGF->GetGO()->LoadCximg(L"img\\background.png", "背景.png", CXIMAGE_FORMAT_PNG);
	bg2=pGF->GetGO()->LoadCximg(L"img\\bg2.png", "bg2.png", CXIMAGE_FORMAT_PNG);
	pGF->GetGO()->LoadCximg(L"img\\Begin1.png", "开始1.png", CXIMAGE_FORMAT_PNG);
	pGF->GetGO()->LoadCximg(L"img\\Begin2.png", "开始2.png", CXIMAGE_FORMAT_PNG);
	pGF->GetGO()->LoadCximg(L"img\\Help1.png", "帮助1.png", CXIMAGE_FORMAT_PNG);
	pGF->GetGO()->LoadCximg(L"img\\Help2.png", "帮助2.png", CXIMAGE_FORMAT_PNG);

	LoadUI(new Button(50, 575, 250, 655, "开始1.png", "开始2.png"), "按钮1", "Game场景");
	LoadUI(new Button(325, 575, 525, 655, "帮助1.png", "帮助2.png"), "按钮2", "Help场景");
}
void MenuScene::Enter()
{
	mTime = 0;
	map<string, UI*>::iterator i;
	for (i = m_UI.begin(); i != m_UI.end(); i++)
	{
		i->second->active = FALSE;
	}
}
void MenuScene::Run(float deltaTime)
{
	if (mTime == 0)
		//sound.play(GAME_MAIN);
		mTime += deltaTime;

	pGF->GetGO()->DrawCximage(bg2->GetWidth() / 2, bg2->GetHeight() / 2, "bg2.png");
	pGF->GetGO()->DrawCximage(287,376, "背景.png");
}
void MenuScene::Quit()
{
	//sound.Stop(GAME_MAIN);
}