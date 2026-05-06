#pragma once
#include<map>
#include "Enum.h"
#include "Defines.h"
using std::map;

class Scene;

class SceneManager
{
#pragma region Single

private:
	SceneManager();
	~SceneManager();
public:
	static SceneManager* GetInst()
	{
		if (nullptr == m_inst)
			m_inst = new SceneManager();
		return m_inst;
	}
	static void DestroyInst() {
		SAFE_DELETE(m_inst);
	}
private:
	static SceneManager* m_inst;

#pragma endregion
public:
	void ChangeScene(SceneType sceneType);
	void InitScenes();
	void Update();
	void Render();
private:
	map<SceneType, Scene*> m_scenes;
	SceneType curSceneType_;
};