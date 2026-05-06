#include <algorithm>
#include "Position.h"
#include "Map.h"
#include "GameManager.h"
#include "MapManager.h"
#include <fcntl.h>
#include <io.h>

using namespace std;

Map::Map(Position pos) : Object(pos), m_gameManager(nullptr), m_mapManager(nullptr) {}

void Map::InitializePosition(const Position& _pos)
{
	GenerateBombs(_pos);
}
void Map::GenerateBombs(const Position& _pos)
{
	srand((unsigned int)time(NULL));

	int cnt = 0;
	vector<unsigned short> indexes;

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (abs(_pos.y - i) > 1 || abs(_pos.x - j) > 1)
			{
				++cnt;
				indexes.push_back((i << 8) + j);
			}
		}
	}

	for (int i = 0; i < 1000; ++i)
	{
		int ind1 = rand() % (cnt);
		int ind2 = rand() % (cnt);

		std::swap(indexes[ind1], indexes[ind2]);
	}

	GenerateMap(indexes);
}

void Map::GenerateMap(const vector<unsigned short> indexes)
{
	for (int i = 0; i < MAP_HEIGHT; ++i)
		for (int j = 0; j < MAP_WIDTH; ++j)
			m_mapManager->m_map[i][j] = new TILE{ EMPTY_TYPE, NumColors[EMPTY_TYPE], GROUND_COLOR };

	int a, x, y;
	for (int i = 0; i < m_gameManager->m_flagCount; ++i)
	{
		a = indexes[i];
		y = a >> 8;
		x = a & 255;
		m_mapManager->m_map[y][x]->type = BOMB_TYPE;
	}

	int mineNear = 0;
	int checkY, checkX;
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			if (m_mapManager->m_map[i][j]->type == BOMB_TYPE)continue;
			mineNear = 0;
			for (int k = 0; k < 8; k++)
			{
				checkY = i + m_checkDirY[k];
				checkX = j + m_checkDirX[k];
				if (checkX < 0 || checkX >= MAP_WIDTH) continue;
				if (checkY < 0 || checkY >= MAP_HEIGHT) continue;
				if (m_mapManager->m_map[checkY][checkX]->type == BOMB_TYPE)
					++mineNear;
			}
			m_mapManager->m_map[i][j]->type = mineNear;
		}
	}
	for (int i = 0; i < MAP_HEIGHT; ++i)
		for (int j = 0; j < MAP_WIDTH; ++j)
			m_mapManager->m_map[i][j]->textColor = NumColors[m_mapManager->m_map[i][j]->type];
}

void Map::Init()
{
	m_gameManager = GameManager::GetInst();
	m_mapManager = MapManager::GetInst();
	m_mapManager->SetMap(this);
	for (int i = 0; i < MAP_HEIGHT; ++i)
		for (int j = 0; j < MAP_WIDTH; ++j)
			m_mapManager->m_revealed[i][j] = TileState::HIDEN;
}

void Map::Update()
{
}

void Map::Render() const
{
	if (!m_mapManager->m_isRendering) return;
	Position selectedPos = m_mapManager->m_selectedPosition;
	int posY = m_pos.y;
	Gotoxy(m_pos.x, m_pos.y);

	int coutmode = _setmode(_fileno(stdout), _O_U16TEXT);

	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			bool isSelected = (selectedPos.x == j && selectedPos.y == i);

			switch (m_mapManager->m_revealed[i][j])
			{
			case TileState::REVEALED:
			{
				PTILE tile = m_mapManager->m_map[i][j];
				SetColor(tile->textColor, isSelected ? SELECT_COLOR : GROUND_COLOR);

				if (tile->type == EMPTY_TYPE)
					wcout << L"  ";
				else if (tile->type == BOMB_TYPE)
				{
					SetColor(tile->textColor, tile->textColor);
					wcout << L"  ";
				}
				else
					wcout << L" " << tile->type;
				break;
			}
			case TileState::HIDEN:
				SetColor(GRASS_COLOR, isSelected ? SELECT_COLOR : GRASS_COLOR);
				wcout << L"  ";
				break;
			case TileState::FLAG:
				SetColor(FLAG_COLOR, isSelected ? SELECT_COLOR : GRASS_COLOR);
				wcout << L"⚑ ";
				break;
			default:
				wcout << L"??";
				break;
			}
		}
		++posY;
		Gotoxy(m_pos.x, posY);
	}
	int wcoutmode = _setmode(_fileno(stdout), coutmode);

	SetColor();
}

void Map::Hide()
{
	int posY = m_pos.y;
	Gotoxy(m_pos.x, m_pos.y);

	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			cout << "  ";
		}
		++posY;
		Gotoxy(m_pos.x, posY);
	}
}
