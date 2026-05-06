#pragma once
#include<map>
#include"Enum.h"
using std::map;

class Scene;
class SceneManager;

class Core
{
public:
	Core();
	void Run();
private:
	void Update();
	void Render();

	SceneManager* m_sceneManager;
};