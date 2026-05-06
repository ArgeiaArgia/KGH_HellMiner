#include <algorithm>
#include "Player.h"
#include "Console.h"
#include "MapManager.h"
#include"GameManager.h"
#include "Mci.h"

Player::Player(Position _pos) : Object(_pos), m_mapManager(nullptr), m_gameManager(nullptr)
{
	_pos.y -= UI_HEIGHT;
	m_pos = _pos;
}

void Player::Init()
{
	m_mapManager = MapManager::GetInst();
	m_gameManager = GameManager::GetInst();
	m_sceneManager = SceneManager::GetInst();
}

void Player::Update()
{
	if (!m_isActive) return;
	m_mapManager->m_selectedPosition = m_pos;
}

void Player::Render() const
{
}

void Player::Move(Dir _dir)
{
	if (!m_isActive) return;
	switch (_dir)
	{
	case Dir::UP:
		--m_pos.y;
		break;
	case Dir::DOWN:
		++m_pos.y;
		break;
	case Dir::LEFT:
		--m_pos.x;
		break;
	case Dir::RIGHT:
		++m_pos.x;
		break;
	}
	m_pos.x = std::clamp(m_pos.x, 0, MAP_WIDTH - 1);
	m_pos.y = std::clamp(m_pos.y, 0, MAP_HEIGHT - 1);
	if (!m_gameManager->m_isPlaying) return;
	++m_gameManager->m_moveCount;
}

void Player::Act(Action _act)
{
	if (_act == Action::RESET)
		return Reset();
	if (_act == Action::TITLE)
	{
		Reset();
		m_sceneManager->ChangeScene(SceneType::TITLE);
		return;
	}
	if (!m_isActive) return;
	switch (_act)
	{
	case Action::DIG:
	{
		int dugCnt = 0;
		Dig(m_pos, dugCnt, false);

		if (dugCnt == 1)
			PlaySoundID(SOUNDID::DIG);
		else if (dugCnt > 1)
			PlaySoundID(SOUNDID::LARGEDIG);

		CheckWin();
		break;
	}
	case Action::FLAG:
		Flag();
		break;
	default:
		break;
	}
}

void Player::Reset()
{
	m_mapManager->ShowMap();
	m_mapManager->ResetGame();
	m_gameManager->ResetGame();
	m_pos = { 0,0 };
	m_isActive = true;
	return;
}

void Player::Dig(const Position& _pos, int& dugCount, bool isAuto = true)
{
	if (!m_mapManager->m_isInitialized)
	{
		m_gameManager->StartGame();
		m_mapManager->InitializePosition(_pos);
	}

	if (!isAuto && m_mapManager->m_revealed[_pos.y][_pos.x] == TileState::REVEALED)
	{
		CheckNum(_pos, dugCount);
		return;
	}
	else if (m_mapManager->m_revealed[_pos.y][_pos.x] == TileState::FLAG)
		return;

	m_mapManager->m_revealed[_pos.y][_pos.x] = TileState::REVEALED;

	if (m_mapManager->m_map[_pos.y][_pos.x]->type == 0)
	{
		Position nextPos;
		for (int i = 0; i < 8; i++)
		{
			nextPos = _pos;
			nextPos.x += m_checkX[i];
			nextPos.y += m_checkY[i];
			if (nextPos.x < 0 || nextPos.x >= MAP_WIDTH) continue;
			if (nextPos.y < 0 || nextPos.y >= MAP_HEIGHT) continue;
			if (m_mapManager->m_revealed[nextPos.y][nextPos.x] == TileState::HIDEN)
				Dig(nextPos, dugCount);
		}
	}
	else if (m_mapManager->m_map[_pos.y][_pos.x]->type == 9)
	{
		m_isActive = false;
		m_gameManager->EndGame();
		m_mapManager->Explosion();
	}
	else
		++dugCount;
}

void Player::CheckNum(const Position& _pos, int& dugCount)
{
	if (m_mapManager->m_map[_pos.y][_pos.x]->type == 0) return;
	int cnt = 0;
	Position nextPos;
	for (int i = 0; i < 8; i++)
	{
		nextPos = _pos;
		nextPos.x += m_checkX[i];
		nextPos.y += m_checkY[i];
		if (nextPos.x < 0 || nextPos.x >= MAP_WIDTH) continue;
		if (nextPos.y < 0 || nextPos.y >= MAP_HEIGHT) continue;
		if (m_mapManager->m_revealed[nextPos.y][nextPos.x] == TileState::FLAG)
			++cnt;
	}
	if (cnt == m_mapManager->m_map[_pos.y][_pos.x]->type)
	{
		for (int i = 0; i < 8; i++)
		{
			nextPos = _pos;
			nextPos.x += m_checkX[i];
			nextPos.y += m_checkY[i];
			if (nextPos.x < 0 || nextPos.x >= MAP_WIDTH) continue;
			if (nextPos.y < 0 || nextPos.y >= MAP_HEIGHT) continue;
			if (m_mapManager->m_revealed[nextPos.y][nextPos.x] == TileState::FLAG)
				continue;

			Dig(nextPos, dugCount);
		}
	}
}

void Player::Flag()
{
	if (!m_mapManager->m_isInitialized) return;
	auto& revealed = m_mapManager->m_revealed[m_pos.y][m_pos.x];
	if (revealed == TileState::REVEALED)return;

	if ((revealed == TileState::HIDEN))
	{
		revealed = TileState::FLAG;
		PlaySoundID(SOUNDID::FLAG);
		--m_gameManager->m_flagCount;
	}
	else
	{
		revealed = TileState::HIDEN;
		++m_gameManager->m_flagCount;
	}
}

void Player::CheckWin()
{
	if (!m_gameManager->m_isPlaying) return;
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if ((m_mapManager->m_map[i][j]->type != BOMB_TYPE) && (m_mapManager->m_revealed[i][j] != TileState::REVEALED))
			{
				return;
			}
		}
	}
	PlaySoundID(SOUNDID::WIN);
	m_isActive = false;
	m_gameManager->FinishGame();
	m_mapManager->HideMap();
}
