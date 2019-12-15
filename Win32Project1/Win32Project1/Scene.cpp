#include"Scene.h"

CSoundManage Scene::sound;
void Scene::Loadmusic()
{
	sound.ReadFile(GAME_MAIN, "sound\\background.mp3", DOSOUND);
	sound.ReadFile(HURT, "sound\\hurt.wav", DOSOUND);
	sound.ReadFile(ON, "sound\\normal_on.wav", DOSOUND);
	sound.ReadFile(DIE, "sound\\die.wav", DOSOUND);
	sound.ReadFile(BUTTON, "sound\\coin.wav", DOSOUND);
	sound.ReadFile(READYGO, "sound\\readygo.mp3", DOSOUND);
	sound.ReadFile(FLIPON, "sound\\flip_on.wav", DOSOUND);
}
Scene::Scene():
m_KeyUI(0)
{}
Scene::~Scene()
{
	map<string, UI*>::iterator i;
	for (i = m_UI.begin(); i != m_UI.end(); i++)
	{
		i->second->End();
		delete i->second;
	}
}

BOOL Scene::LoadUI(UI* pUI, const string ID, const string SceneID)
{
	if (m_UI[ID])
		return FALSE;
	pUI->BelongScene = this;
	pUI->SceneID = SceneID;
	pUI->Init();
	m_UI[ID] = pUI;
}
BOOL Scene::ReleaseUI(const string ID)
{
	map<string, UI*>::iterator i = m_UI.find(ID);
	if (i == m_UI.end())
		return FALSE;
	i->second->End();
	delete i->second;
	m_UI.erase(i);
}
BOOL Scene::SetUI(const string ID)
{
	if (ID.empty())
		m_KeyUI = 0;
	else
	{
		map<string, UI*>::iterator i = m_UI.find(ID);
		if (i == m_UI.end())
			return FALSE;
			m_KeyUI = i->second;
	}
	return TRUE;
}

void Scene::Init(){}
void Scene::Enter(){}
void Scene::Run(float deltaTime){}
void Scene::Quit(){}
void Scene::End(){}