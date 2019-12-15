#include"Game.h"
#include"time.h"

float GameScene::mGameSpeed=150;
void GameScene::Init()
{
	pGF = GameFrame::GetObject();
	mhDC = pGF->GetGO()->GethMemDC();
	mTime = 0;
	srand(time(NULL));
	pGF->GetGO()->LoadCximg(L"img\\returnMenu1.png", "返回主菜单1.png", CXIMAGE_FORMAT_PNG);
	pGF->GetGO()->LoadCximg(L"img\\returnMenu2.png", "返回主菜单2.png", CXIMAGE_FORMAT_PNG);
	pGF->GetGO()->LoadCximg(L"img\\again1.png", "不服再战1.png", CXIMAGE_FORMAT_PNG);
	pGF->GetGO()->LoadCximg(L"img\\again2.png", "不服再战2.png", CXIMAGE_FORMAT_PNG);


	mRole = new cRole(120,200,200,190);

	mBg = new cBackground(mhDC);

	ObstacleMgr = new cObstacleMgr();
}
void GameScene::Enter()
{
	mTime = 0;
	mGameSpeed = 150;
	mEnd = FALSE;
	mRole->Enter();
	ObstacleMgr->Enter();
	mBg->Enter();
}
void GameScene::Run(float deltaTime)
{
	if (mTime == 0)
		Scene::sound.play(READYGO);
	mTime += deltaTime;
	if (mTime <1 && mTime + deltaTime>1)
		Scene::sound.play(GAME_MAIN);

	if (!mEnd && mRole->GetIfDie())
	{
		mEnd = TRUE;
		LoadUI(new Button(20, 500, 260, 560, "不服再战2.png", "不服再战1.png"), "按钮1", "Game场景");
		LoadUI(new Button(300, 500, 540, 560, "返回主菜单2.png", "返回主菜单1.png"), "按钮2", "Menu场景");
	}

	mBg->Draw(mhDC);
	mRole->Draw(mhDC);
	ObstacleMgr->Draw(mhDC);

	mBg->Draw2(mhDC);


	if (mTime < 2)
	{
		if (mTime<1)
			mBg->DrawReady(mhDC);
		else
			mBg->DrawGo(mhDC);
		return;
	}
	if (mEnd)
	{
		mBg->Draw3(mhDC);
		return;
	}
	if (mGameSpeed<300)
		mGameSpeed += deltaTime*2;
	mRole->Update(deltaTime);
	ObstacleMgr->Update(deltaTime);
	mBg->Update(deltaTime);

}
void GameScene::Quit()
{
	ObstacleMgr->ClearAll();
	ReleaseUI("按钮1");
	ReleaseUI("按钮2");
	Scene::sound.Stop(GAME_MAIN);
}
void GameScene::End()
{
	delete mRole;
	delete ObstacleMgr;
	delete mBg;
	
}