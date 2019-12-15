#include "Background.h"
#include"Game.h"

cBackground::cBackground(HDC hdc) :
mTime(0)
{
	mBg1_y = 0;

	CxImage* img2 = new CxImage(L"img\\blood.png", CXIMAGE_FORMAT_PNG);
	bw2 = img2->GetWidth();
	bh2 = img2->GetHeight();
	mLifeDC = CreateCompatibleDC(hdc);
	HBITMAP bm2 = img2->MakeBitmap(mLifeDC);
	SelectObject(mLifeDC, bm2);
	DeleteObject(bm2);
	//delete img2;

	CxImage* img1 = new CxImage(L"img\\border.png", CXIMAGE_FORMAT_PNG);
	bw1 = img1->GetWidth();
	bh1 = img1->GetHeight();
	mBorderDC = CreateCompatibleDC(hdc);
	HBITMAP bm1 = img1->MakeBitmap(mBorderDC);
	SelectObject(mBorderDC, bm1);
	DeleteObject(bm1);
	//delete img1;

	pGF = GameFrame::GetObject();
	bg1 = pGF->GetGO()->LoadCximg(L"img\\bg1.png", "bg1.png", CXIMAGE_FORMAT_PNG);
	bg2 = pGF->GetGO()->LoadCximg(L"img\\bg2.png", "bg2.png", CXIMAGE_FORMAT_PNG);
	TopCi = pGF->GetGO()->LoadCximg(L"img\\TopCi.png", "TopCi.png", CXIMAGE_FORMAT_PNG);
	mLife_bg = pGF->GetGO()->LoadCximg(L"img\\blood_bg.png", "blood_bg.png", CXIMAGE_FORMAT_PNG);
	mScore_bg = pGF->GetGO()->LoadCximg(L"img\\score_bg.png", "score_bg.png", CXIMAGE_FORMAT_PNG);
	mEnd = pGF->GetGO()->LoadCximg(L"img\\gameover.png", "gameover.png", CXIMAGE_FORMAT_PNG);
	mReadr=pGF->GetGO()->LoadCximg(L"img\\ready.png", "ready.png", CXIMAGE_FORMAT_PNG);
	mGo = pGF->GetGO()->LoadCximg(L"img\\go.png", "go.png", CXIMAGE_FORMAT_PNG);

	mNum = new cImg*[10];
	mNum[0] = pGF->GetGO()->LoadCximg(L"img\\0.png", "0.png", CXIMAGE_FORMAT_PNG);
	mNum[1] = pGF->GetGO()->LoadCximg(L"img\\1.png", "1.png", CXIMAGE_FORMAT_PNG);
	mNum[2] = pGF->GetGO()->LoadCximg(L"img\\2.png", "2.png", CXIMAGE_FORMAT_PNG);
	mNum[3] = pGF->GetGO()->LoadCximg(L"img\\3.png", "3.png", CXIMAGE_FORMAT_PNG);
	mNum[4] = pGF->GetGO()->LoadCximg(L"img\\4.png", "4.png", CXIMAGE_FORMAT_PNG);
	mNum[5] = pGF->GetGO()->LoadCximg(L"img\\5.png", "5.png", CXIMAGE_FORMAT_PNG);
	mNum[6] = pGF->GetGO()->LoadCximg(L"img\\6.png", "6.png", CXIMAGE_FORMAT_PNG);
	mNum[7] = pGF->GetGO()->LoadCximg(L"img\\7.png", "7.png", CXIMAGE_FORMAT_PNG);
	mNum[8] = pGF->GetGO()->LoadCximg(L"img\\8.png", "8.png", CXIMAGE_FORMAT_PNG);
	mNum[9] = pGF->GetGO()->LoadCximg(L"img\\9.png", "9.png", CXIMAGE_FORMAT_PNG);

}
cBackground::~cBackground()
{
	DeleteDC(mBorderDC);
	DeleteDC(mLifeDC);

	delete mNum;
}
void cBackground::Enter()
{
	mTime = 0;
	mBg1_y = 0;
}
void cBackground::Update(float deltaTime)
{
	mTime += deltaTime;
	mBg1_y += GameScene::mGameSpeed*deltaTime;
	if (mBg1_y > bh1)
		mBg1_y = 0;

}
void cBackground::Draw(HDC hdc)
{
	bg1->Draw(hdc, ClientW / 2, ClientH/2+38);
	BitBlt(hdc, 24, 0, bw1, ClientH, mBorderDC, 0, mBg1_y, SRCCOPY);
	BitBlt(hdc, ClientW - bw1 - 24, 0, bw1, ClientH, mBorderDC, 0, mBg1_y, SRCCOPY);
	if (mBg1_y + ClientH > bh1)
	{
		BitBlt(hdc, 24, bh1 - mBg1_y, bw1, mBg1_y + ClientH - bh1, mBorderDC, 0, 0, SRCCOPY);
		BitBlt(hdc, ClientW - bw1 - 24, bh1 - mBg1_y, bw1, mBg1_y + ClientH - bh1, mBorderDC, 0, 0, SRCCOPY);
	}
}
void cBackground::Draw2(HDC hdc)
{
	TopCi->Draw(hdc, ClientW / 2, TopCi->GetHeight() / 2 + 76);
	bg2->Draw(hdc, ClientW / 2, ClientH / 2);

	mLife_bg->Draw(hdc,175,41);
	BitBlt(hdc, 130, 25, cRole::mHP, bh2, mLifeDC, 0, 0, SRCCOPY);

	mScore_bg->Draw(hdc, 475, 41);


	int a = cRole::mScore;
	do
	{
		score.push(a % 10);
		a /= 10;
	} while (a != 0);
	float beginX = 475;
	if (score.size() > 1)
	{
		beginX -= (score.size()-1)*11;
	}
	int i = 0;
	while (score.size() > 0)
	{
		mNum[score.top()]->Draw(hdc, beginX + i * 22, 40);
		score.pop();
		i++;
	}
}
void cBackground::Draw3(HDC hdc)
{
	mEnd->Draw(hdc,ClientW / 2, ClientH / 2);
}
void cBackground::EndDraw(HDC hdc)
{
	Draw(hdc);
	mEnd->Draw(hdc,400,200);
}
void cBackground::DrawReady(HDC hdc)
{
	mReadr->Draw(hdc, ClientW / 2, ClientH / 2);
}
void cBackground::DrawGo(HDC hdc)
{
	mGo->Draw(hdc, ClientW / 2, ClientH / 2);
}

