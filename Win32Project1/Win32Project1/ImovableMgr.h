#ifndef _IMOVABLEMGR_H_
#define _IMOVABLEMGR_H_

#include "IMovable.h"
#include <list>
using namespace std;

class cMovableMgr
{
protected:
	list<cIMovable *> mMovableList;
public:
	cMovableMgr();
	~cMovableMgr();
	virtual void Draw(HDC hdc);
	virtual void Update(float deltaTime);

	UINT GetMovableCount()
	{
		return mMovableList.size();
	}

	void AddMovable(cIMovable * movable);
	void EraseMovable(cIMovable *movable);
	void ClearAll();
};
#endif
