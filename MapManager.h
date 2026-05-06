#pragma once
#include "Defines.h"
#include "Tile.h"
#include "Enum.h"
#include "Position.h"
class Map;
class MapManager
{
#pragma region Single

private:
	MapManager();
	~MapManager();
public:
	static MapManager* GetInst()
	{
		if (nullptr == m_inst)
			m_inst = new MapManager();
		return m_inst;
	}
	static void DestroyInst() {
		SAFE_DELETE(m_inst);
	}
private:
	static MapManager* m_inst;

#pragma endregion
public:
	void SetMap(Map* map);

	void ResetGame();
	void InitializePosition(const Position& _pos);
	void Explosion();

	void ShowMap();
	void HideMap();

	Position m_selectedPosition;
	PTILE m_map[MAP_HEIGHT][MAP_WIDTH];
	TileState m_revealed[MAP_HEIGHT][MAP_WIDTH];

	bool m_isInitialized = false;
	bool m_didEnd = false;
	bool m_isRendering = true;
private:
	Map* m_curMap;
};

