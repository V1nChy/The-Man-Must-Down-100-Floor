#include "ImovableMgr.h"

cMovableMgr::cMovableMgr()
{
}


cMovableMgr::~cMovableMgr()
{
	list<cIMovable *>::iterator it = mMovableList.begin(), end = mMovableList.end();
	for (; it != end; it++)
		delete(*it);
}


void cMovableMgr::Draw(HDC hdc)
{
	list<cIMovable *>::iterator it = mMovableList.begin(), end = mMovableList.end();
	for (; it != end; it++)
		(*it)->Draw(hdc);
}


void cMovableMgr::Update(float deltaTime)
{
	list<cIMovable *>::iterator it = mMovableList.begin(), end = mMovableList.end(), temp;
	for (; it != end;)
	{
		temp = it;
		it++;
		(*temp)->Update(deltaTime);
	}
}

void cMovableMgr::AddMovable(cIMovable * movable)
{
	mMovableList.push_back(movable);
}

void cMovableMgr::EraseMovable(cIMovable *movable)
{
	list<cIMovable *>::iterator it = mMovableList.begin(), end = mMovableList.end(), temp;
	for (; it != end; it++){
		if (*it == movable)
		{
			delete (*it);
			mMovableList.erase(it);
			return;
		}
	}
}
void cMovableMgr::ClearAll()
{
	list<cIMovable *>::iterator it = mMovableList.begin(), end = mMovableList.end(), temp;
	for (; it != end; it++)
	{
		delete (*it);
	}
	mMovableList.clear();
}
