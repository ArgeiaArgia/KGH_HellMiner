#pragma once
#include "Object.h"
#include "IMovable.h"
#include "IActionable.h"
#include "Position.h"
#include "SceneManager.h"

class MapManager;
class GameManager;
class Player : public Object, public IMovable, public IActable
{
public:
	Player(Position _pos = { 0,0 });
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() const override;
	virtual void Move(Dir _dir) override;
	virtual void Act(Action _act) override;
	void Reset();
private:
	void Dig(const Position& _pos, int& dugCount, bool isAuto);
	void CheckNum(const Position& _pos, int& dugCount);
	void Flag();
	void CheckWin();
private:
	MapManager* m_mapManager;
	GameManager* m_gameManager;
	SceneManager* m_sceneManager;

	bool m_isActive = true;

	const int m_checkX[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	const int m_checkY[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
};