#pragma once
#include "Scene.h"
#include "Map.h"
#include "InputHandler.h"

class GameScene : public Scene
{
public:
	GameScene();
public:
	virtual void Update() override;
private:
	InputHandler m_inputHandler;
};