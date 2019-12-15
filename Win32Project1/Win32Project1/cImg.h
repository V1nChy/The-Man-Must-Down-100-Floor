#ifndef _CIMG_H_
#define _CIMG_H_

#include "ximage.h"
#include "BasicData.h"

// ��װCxImage
class cImg
{
private:
	CxImage * mCximg;	// ��װ��CxImage
	float w, h;			// ͼƬ�ĸ߶ȺͿ��
public:
	cImg(TCHAR * filename, ENUM_CXIMAGE_FORMATS format);
	~cImg(void);
	// ��(x,y)����תangle��
	void Draw(HDC hdc, UINT x, UINT y, double angle = 0);
	float GetWidth();
	float GetHeight();

	void SetJitte(int n);//�����������
	void SetNoise(int n);//���
	void SetGrayScale();//�Ҷ�
	void SetLight(int x, int y);//���ȺͶԱȶ�
	void SetResampl(int x, int y);//������С
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