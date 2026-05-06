#include "SceneManager.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "TitleScene.h"

SceneManager* SceneManager::m_inst = nullptr;

SceneManager::SceneManager() : curSceneType_(SceneType::TITLE)

{
	m_scenes[SceneType::TITLE] = new TitleScene();
	m_scenes[SceneType::INFO] = new SelectScene();
	m_scenes[SceneType::GAME] = new GameScene();
}

SceneManager::~SceneManager()
{
	for (auto& s : m_scenes)
	{
		SAFE_DELETE(s.second);
	}
	m_scenes.clear();
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	for (int i = 0; i < 22; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			Gotoxy(j * 2, i);
			SetColor(COLOR::WHITE, (i + j) % 2 == 0 ? COLOR::LIGHT_GREEN : COLOR::LIGHT_YELLOW);
			cout << "  ";
		}
		Sleep(80);
	}
	SetColor(COLOR::WHITE, COLOR::BLACK);
	system("cls");
	curSceneType_ = sceneType;
}

void SceneManager::InitScenes()
{
	for (auto& s : m_scenes)
	{
		s.second->Init();
	}
}

void SceneManager::Update()
{
		m_scenes[curSceneType_]->Update();
}

void SceneManager::Render()
{
		m_scenes[curSceneType_]->Render();
}