#include <ctime>
#include "GameManager.h"
#include "Console.h"

GameManager* GameManager::m_inst = nullptr;

GameManager::GameManager()
	: m_flagCount(35), m_playTime(0), m_moveCount(0),
	m_conditionValue(150), m_condition(Challenge::NONE),
	m_curStage(0), m_moveStage({ 0 }), m_timeStage({ 0 })
{
}

void GameManager::CountTime()
{
	if (m_isPlaying)
	{
		m_playTime++;
	}
}

void GameManager::SetCondition(Challenge _cond, int _value, int _stage)
{
	m_condition = _cond;
	m_conditionValue = _value;
	m_curStage = _stage;
}

void GameManager::ResetGame()
{
	m_isPlaying = false;
	m_flagCount = 35;
	m_playTime = 0;
	m_moveCount = 0;
}

void GameManager::StartGame()
{
	m_isPlaying = true;
}

void GameManager::EndGame()
{
	m_isPlaying = false;
}

void GameManager::FinishGame()
{
	m_isPlaying = false;
	int curStar = 0;
	if (m_condition == Challenge::TIME)
	{
		for (int i = 1; i <= 3; i++)
		{
			if (m_playTime < (m_conditionValue - i * 10))
				curStar = i;
		}
		m_timeStage[m_curStage] = m_timeStage[m_curStage] > curStar ? m_timeStage[m_curStage] : curStar;
	}
	else
	{
		for (int i = 1; i <= 3; i++)
		{
			if (m_moveCount < (m_conditionValue - i * 20))
				curStar = i;
		}
		m_moveStage[m_curStage] = m_moveStage[m_curStage] > curStar ? m_moveStage[m_curStage] : curStar;
	}
}
