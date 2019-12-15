#ifndef _CIMG_H_
#define _CIMG_H_

#include "ximage.h"
#include "BasicData.h"

// 封装CxImage
class cImg
{
private:
	CxImage * mCximg;	// 封装的CxImage
	float w, h;			// 图片的高度和宽度
public:
	cImg(TCHAR * filename, ENUM_CXIMAGE_FORMATS format);
	~cImg(void);
	// 在(x,y)处旋转angle°
	void Draw(HDC hdc, UINT x, UINT y, double angle = 0);
	float GetWidth();
	float GetHeight();

	void SetJitte(int n);//随机抵消像素
	void SetNoise(int n);//噪点
	void SetGrayScale();//灰度
	void SetLight(int x, int y);//亮度和对比度
	void SetResampl(int x, int y);//调整大小
};

class cImgManager
{
protected:
	static map<string, cImg*> mImgMap;
public:
	cImgManager();
	~cImgManager();

	static cImg* CreateImg(TCHAR* fileName, const string ID, DWORD format);
	static cImg* SetImg(const string ID);

	static int GetSize()
	{
		return mImgMap.size();
	}
	static void ClearAll();
};
#endif