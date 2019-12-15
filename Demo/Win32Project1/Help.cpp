#include"Help.h"

void HelpScene::Init()
{
	pGF = GameFrame::GetObject();
	mTtime = 0;

	bg1 = pGF->GetGO()->LoadCximg(L"img\\bg1.png", "bg1.png", CXIMAGE_FORMAT_PNG);
	bg2 = pGF->GetGO()->LoadCximg(L"img\\bg2.png", "bg2.png", CXIMAGE_FORMAT_PNG);
	bg3 = pGF->GetGO()->LoadCximg(L"img\\help.png", "help.png", CXIMAGE_FORMAT_PNG);
	pGF->GetGO()->LoadCximg(L"img\\return1.png", "返回1.png", CXIMAGE_FORMAT_PNG);
	pGF->GetGO()->LoadCximg(L"img\\return2.png", "返回2.png", CXIMAGE_FORMAT_PNG);


	LoadUI(new Button(400, 600, 500, 640, "返回1.png", "返回2.png"), "按钮1", "Menu场景");

}
void HelpScene::Enter()
{
	mTtime = 0;
	map<string, UI*>::iterator i;
	for (i = m_UI.begin(); i != m_UI.end(); i++)
	{
		i->second->active = FALSE;
	}
}
void HelpScene::Run(float deltaTime)
{
	pGF->GetGO()->DrawCximage(bg2->GetWidth() / 2, bg2->GetHeight() / 2, "bg2.png");
	pGF->GetGO()->DrawCximage(287, 376, "bg1.png");
	pGF->GetGO()->DrawCximage(287, 376, "help.png");
}
void HelpScene::Quit()
{}