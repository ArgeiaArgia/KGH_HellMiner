#include "MapManager.h"
#include "Map.h"
#include "Mci.h"

MapManager* MapManager::m_inst = nullptr;

MapManager::MapManager() : m_map{ nullptr }, m_revealed{ TileState::HIDEN }
{
}

MapManager::~MapManager()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			SAFE_DELETE(m_map[i][j]);
		}
	}
	m_curMap = nullptr;
}

void MapManager::SetMap(Map* map)
{
	m_curMap = map;
}

void MapManager::ResetGame()
{
	m_isInitialized = false;
	m_didEnd = false;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			m_revealed[i][j] = TileState::HIDEN;
		}
	}
}

void MapManager::InitializePosition(const Position& _pos)
{
	m_isInitialized = true;
	m_curMap->InitializePosition(_pos);
}

void MapManager::Explosion()
{
	PlaySoundID(SOUNDID::EXPLOSION);
	m_didEnd = true;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			m_revealed[i][j] = TileState::REVEALED;
		}
	}
}

void MapManager::ShowMap()
{
	m_isRendering = true;
	
}

void MapManager::HideMap()
{
	m_isRendering = false;
	m_curMap->Hide();
}