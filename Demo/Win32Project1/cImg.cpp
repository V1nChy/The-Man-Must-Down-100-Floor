#include "cImg.h"

cImg::cImg(TCHAR * filename, ENUM_CXIMAGE_FORMATS format)
{
	mCximg = new CxImage;
	if (mCximg->Load(filename, format))
	{
		w = mCximg->GetWidth();
		h = mCximg->GetHeight();
	}
	else
	{
		mCximg = NULL;
		w = 0;
		h = 0;
	}
}

cImg::~cImg(void)
{
	if (mCximg)
	{
		delete mCximg;
		mCximg = NULL;
	}
}

void cImg::Draw(HDC hdc, UINT x, UINT y, double angle)
{
	if (!mCximg) return;

	if (fabs(angle) < 1e-6)
	{
		mCximg->Draw(hdc, x - w / 2, y - h / 2);
	}
	else
	{
		CxImage temp;
		mCximg->Rotate(angle, &temp);
		temp.Draw(hdc, x - temp.GetWidth() / 2, y - temp.GetHeight() / 2);
	}
}

float cImg::GetWidth()
{
	return w;
}

float cImg::GetHeight()
{
	return h;
}

void cImg::SetJitte(int n)
{
	mCximg->Jitter(n);
}
void cImg::SetNoise(int n)
{
	mCximg->Noise(n);
}
void cImg::SetGrayScale()
{
	mCximg->GrayScale();
}
void cImg::SetLight(int x, int y)
{
	mCximg->Light(x, y);
}
void cImg::SetResampl(int x, int y)
{
	mCximg->Resample(x, y, 3);
}






map<string, cImg*> cImgManager::mImgMap;
cImgManager::cImgManager()
{
}

cImgManager::~cImgManager()
{
}

cImg* cImgManager::CreateImg(TCHAR* fileName, const string ID, DWORD format)
{
	cImg* tempImg = NULL;
	wstring str = wstring(fileName);
	tempImg = mImgMap[ID];

	if (!tempImg)
	{
		// 没有这个图片
		tempImg = new cImg(fileName, (ENUM_CXIMAGE_FORMATS)format);
		mImgMap[ID] = tempImg;
		return tempImg;
	}
	else
	{
		return tempImg;
	}
}

cImg* cImgManager::SetImg(const string ID)
{
	return mImgMap[ID];
}

void cImgManager::ClearAll()
{
	map<string, cImg*>::iterator i;
	for (i = mImgMap.begin(); i != mImgMap.end(); i++)
		delete (i->second);
}
