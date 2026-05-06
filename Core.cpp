#include "Core.h"
#include "Console.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Mci.h"

Core::Core(): m_sceneManager(nullptr)
{
	m_sceneManager = SceneManager::GetInst();
}

void Core::Run()
{
	if (!InitAllSounds()) return;
	SetConsoleSettings(1000, 750, false, L"minesweeper");
	SetCursorVisual(false, 10);
	SetConsoleFont(L"MS Gothic", { 13, 24 }, FW_BOLD);
	m_sceneManager->InitScenes();
	PlaySoundID(SOUNDID::BGM, true);

	while (true)
	{
		Update();
		Render();
		FrameSync(60);
	}

	GameManager::DestroyInst();
	SceneManager::DestroyInst();
}

void Core::Update()
{
	m_sceneManager->Update();
}

void Core::Render()
{
	m_sceneManager->Render();
}
