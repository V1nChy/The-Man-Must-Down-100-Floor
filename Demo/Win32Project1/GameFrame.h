#ifndef _GAME_FRAME_H_
#define _GAME_FRAME_H_

#include"BasicData.h"
#include"GameOutput.h"
#include"GameInput.h"
#include"Scene.h"

class GameFrame
{
private:
	//框架相关
	static GameFrame* m_pGameFrame;
	static LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

	WNDCLASS m_WndClass;
	HWND m_hWnd;

	//输入输出场景
	GameOutput* m_pGameOutput;
	GameInput* m_pGameInput;
	map<string, Scene*> m_Scene;
	Scene* m_pScene;
	POINT m_Mouse;

	// 与时间、帧率等相关的变量
	LARGE_INTEGER mFrequency;
	LARGE_INTEGER mStartCount;
	float mFPS;		// 帧率
	float deltaTime; //两帧间隔时间
	BOOL mbIsRun;

	GameFrame();

public:
	//框架相关
	~GameFrame();
	static GameFrame* GetObject();
	void Run();
	void End();
	BOOL Frame();

	//场景相关
	BOOL LoadScene(Scene* pScene, const string ID);
	BOOL ReleaseScene(const string ID);
	BOOL SetScene(const string ID);
	Scene* GetScene(const string ID);

	GameOutput* GetGO();
	GameInput* GetGI();
	BOOL GetIsRun();
};
#endif