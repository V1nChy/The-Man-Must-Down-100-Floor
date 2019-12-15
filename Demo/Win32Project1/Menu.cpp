#include"Menu.h"

void MenuScene::Init()
{
	pGF = GameFrame::GetObject();
	mTime = 0;

	bg1=pGF->GetGO()->LoadCximg(L"img\\background.png", "����.png", CXIMAGE_FORMAT_PNG);
	bg2=pGF->GetGO()->LoadCximg(L"img\\bg2.png", "bg2.png", CXIMAGE_FORMAT_PNG);
	pGF->GetGO()->LoadCximg(L"img\\Begin1.png", "��ʼ1.png", CXIMAGE_FORMAT_PNG);
	pGF->GetGO()->LoadCximg(L"img\\Begin2.png", "��ʼ2.png", CXIMAGE_FORMAT_PNG);
	pGF->GetGO()->LoadCximg(L"img\\Help1.png", "����1.png", CXIMAGE_FORMAT_PNG);
	pGF->GetGO()->LoadCximg(L"img\\Help2.png", "����2.png", CXIMAGE_FORMAT_PNG);

	LoadUI(new Button(50, 575, 250, 655, "��ʼ1.png", "��ʼ2.png"), "��ť1", "Game����");
	LoadUI(new Button(325, 575, 525, 655, "����1.png", "����2.png"), "��ť2", "Help����");
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
	pGF->GetGO()->DrawCximage(287,376, "����.png");
}
void MenuScene::Quit()
{
	//sound.Stop(GAME_MAIN);
}