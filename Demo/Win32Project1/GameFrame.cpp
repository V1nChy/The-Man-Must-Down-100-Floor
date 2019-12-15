#include"GameFrame.h"

#define _SLEEP_TIME 5u
#define _SLEEP_TIME_MIN 1u

GameFrame *GameFrame::m_pGameFrame = 0;
LRESULT CALLBACK GameFrame::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
	{
		POINT mouse = { LOWORD(lParam), HIWORD(lParam) };
		if (m_pGameFrame->m_pScene && !m_pGameFrame->m_pScene->m_UI.empty())
		{
			map<string, UI*>* p = &m_pGameFrame->m_pScene->m_UI;
			map<string, UI*>::iterator i;
			for (i = p->begin(); i != p->end(); i++)
			{
				RECT r = { i->second->x1, i->second->y1, i->second->x2, i->second->y2};
				if (PtInRect(&r, m_pGameFrame->m_Mouse) && !PtInRect(&r, mouse))
					i->second->CursorOutMove();
				else if (!PtInRect(&r, m_pGameFrame->m_Mouse) && PtInRect(&r, mouse))
				{
					i->second->CursorInMove();
					i->second->SetSoundPlay();
				}
				else if (PtInRect(&r, m_pGameFrame->m_Mouse) && PtInRect(&r, mouse))
					i->second->CursorInMove();
				else
					i->second->CursorOutMove();
			}
		}
		m_pGameFrame->m_Mouse = mouse;
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		POINT mouse = { LOWORD(lParam), HIWORD(lParam) };
		if (m_pGameFrame->m_pScene && !m_pGameFrame->m_pScene->m_UI.empty())
		{
			map<string, UI*>* p = &m_pGameFrame->m_pScene->m_UI;
			map<string, UI*>::iterator i;
			if (p->size() == 0)
				return 0;
			for (i = p->begin(); i != p->end(); i++)
			{
				RECT r = { i->second->x1, i->second->y1, i->second->x2, i->second->y2 };
				if (PtInRect(&r, mouse))
				{
					i->second->ButtonDown(i->first);
					break;
				}
			}
		}
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);

	}

}
GameFrame::GameFrame():
m_hWnd(0),
m_pGameOutput(0),
m_pGameInput(0),
m_pScene(0),
deltaTime(0),
mbIsRun(FALSE)
{
	m_WndClass.style = CS_HREDRAW | CS_VREDRAW;
	m_WndClass.lpfnWndProc = WndProc;
	m_WndClass.cbClsExtra = 0;
	m_WndClass.cbWndExtra = 0;
	m_WndClass.hInstance = GetModuleHandle(0);
	m_WndClass.hIcon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_APPLICATION));
	m_WndClass.hCursor = LoadCursor(0, IDC_ARROW);
	m_WndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	m_WndClass.lpszMenuName = 0;
	m_WndClass.lpszClassName = L"GAME";
	
	if (!RegisterClass(&m_WndClass))
		return;
	RECT r =
	{
		(GetSystemMetrics(SM_CXSCREEN) - ClientW) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - ClientH) / 2,
		(GetSystemMetrics(SM_CXSCREEN) - ClientW) / 2 + ClientW,
		(GetSystemMetrics(SM_CYSCREEN) - ClientH) / 2 + ClientH
	};
	AdjustWindowRect(&r, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);
	m_hWnd = CreateWindow(
		m_WndClass.lpszClassName,
		0,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		r.left,
		r.top,
		r.right - r.left,
		r.bottom - r.top,
		HWND_DESKTOP,
		0,
		m_WndClass.hInstance,
		0);
	if (!m_hWnd)
		return;

	m_pGameFrame = this;
	m_pGameOutput = new GameOutput(m_hWnd);
	m_pGameInput = new GameInput();
	m_Mouse.x = 0;
	m_Mouse.y = 0;

	Scene::Loadmusic();

	QueryPerformanceFrequency(&mFrequency);
	QueryPerformanceCounter(&mStartCount);
}
GameFrame::~GameFrame()
{
	map<string, Scene*>::iterator i;
	for (i = m_Scene.begin(); i != m_Scene.end(); i++)
	{
		i->second->End();
		delete i->second;
	}
	delete m_pGameOutput;
	delete m_pGameInput;
	UnregisterClass(m_WndClass.lpszClassName, m_WndClass.hInstance);
}
void GameFrame::Run()
{
	ShowWindow(m_hWnd,SW_SHOW);
	UpdateWindow(m_hWnd);

	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (Frame()==FALSE)
				break;
		}
	}
}
void GameFrame::End()
{
	if (m_pGameFrame)
	{
		delete m_pGameFrame;
		m_pGameFrame = 0;
	}
}
BOOL GameFrame::Frame()
{
	// ��һ֡�ļ���������ʼ��Ϊ�������ʼ������
	static LARGE_INTEGER lastCounter = mStartCount;

	//������Ϣ����
	m_pGameInput->Run(deltaTime);

	if (m_pGameInput->mESC)
	{
		return FALSE;
	}

	//��Ϸ��ͣ
	HWND hForegroundWindow = GetForegroundWindow();
	BOOL bIsForeground = (m_hWnd == hForegroundWindow); // �ǵ�ǰ������Զ����ͣ״̬

	static BOOL bLastSpaceDown = FALSE;	// ��һ֡�ո���Ƿ���
	BOOL bCurSpaceDown = m_pGameInput->mSPACE;	// ��ǰ֡�ո���Ƿ���
	if (bCurSpaceDown && (!bLastSpaceDown))	// �����ո��
	{
		mbIsRun = !mbIsRun;
	}
	bLastSpaceDown = bCurSpaceDown;			// ��¼�ո���ĵ�ǰ״̬���Ա���һ֡ʹ��
	if (mbIsRun)
	{
		QueryPerformanceCounter(&lastCounter);
		return TRUE;
	}

/*--------------------------------------------------------------------------------*/
	//���
	m_pGameOutput->BeginOutput();
	if (m_pScene)
	{
		m_pScene->Run(deltaTime);
		map<string, UI*>::iterator i;
		for (i = m_pScene->m_UI.begin(); i != m_pScene->m_UI.end(); i++)
		{
			i->second->Render();
		}
	}

	// ��(��һ��)֡�ʵ�������Ϣ��ʾ����Ļ��
	static TCHAR temp[100];
	_stprintf(temp, L"FPS :%3d", (int)mFPS);
	m_pGameOutput->DrawText(temp,0,0);

	m_pGameOutput->EndOutput();
	Sleep(deltaTime < (unsigned int)_SLEEP_TIME ? _SLEEP_TIME - deltaTime : _SLEEP_TIME_MIN);
/*--------------------------------------------------------------------------------*/

	//����֡��
	// ��ѯ��ǰ�ļ�����
	LARGE_INTEGER currentCounter;
	QueryPerformanceCounter(&currentCounter);
	// ��֮֡���ʱ����
	deltaTime = (float)(currentCounter.LowPart - lastCounter.LowPart) / mFrequency.LowPart;
	mFPS = 1.0f / deltaTime;	// ���㵱ǰ��֡��
	lastCounter = currentCounter;	// �ѵ�ǰ�ļ����������ھ�̬������

	return TRUE;
}
GameFrame* GameFrame::GetObject()
{
	if (!m_pGameFrame)
		m_pGameFrame = new GameFrame;
	return m_pGameFrame;
}
GameOutput* GameFrame::GetGO()
{
	return m_pGameOutput;
}
GameInput* GameFrame::GetGI()
{
	return m_pGameInput;
}

BOOL GameFrame::LoadScene(Scene* pScene, const string ID)
{
	if (!m_Scene[ID])
	{
		pScene->Init();
		m_Scene[ID] = pScene;
	}
	else
		return FALSE;
	return TRUE;
}
BOOL GameFrame::ReleaseScene(const string ID)
{
	map<string, Scene*>::iterator i = m_Scene.find(ID);
	if (i == m_Scene.end())
		return FALSE;
	i->second->End();
	delete i->second;
	m_Scene.erase(i);
	return TRUE;
}
BOOL GameFrame::SetScene(const string ID)
{
	map<string, Scene*>::iterator i = m_Scene.find(ID);
	if (i == m_Scene.end())
		return FALSE;
	if (m_pScene)
		m_pScene->Quit();
	m_pScene = i->second;
	m_pScene->Enter();
	return TRUE;
}
Scene* GameFrame::GetScene(const string ID)
{
	map<string, Scene*>::iterator i = m_Scene.find(ID);
	return i != m_Scene.end() ? i->second : 0;
}

BOOL GameFrame::GetIsRun()
{
	return mbIsRun;
}