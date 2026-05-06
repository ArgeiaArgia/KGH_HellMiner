#pragma once
#include "Enum.h"
#include "Defines.h"
class GameManager
{
#pragma region Single

private:
	GameManager();
public:
	static GameManager* GetInst()
	{
		if (nullptr == m_inst)
			m_inst = new GameManager();
		return m_inst;
	}
	static void DestroyInst() {
		SAFE_DELETE(m_inst);
	}
private:
	static GameManager* m_inst;

#pragma endregion
public:
	int m_flagCount; //남은 깃발 수
	int m_playTime; //플레이 타임
	int m_moveCount; //움직임 횟수

	int m_conditionValue; // 현재 조건 최대 값 (시간이나 움직임)
	Challenge m_condition; // 조건 (시간이나 움직임)
	bool m_isPlaying = false;
	
public:
	void  CountTime();
	void SetCondition(Challenge _cond, int _value, int _stage); //조건 정해주기
	void ResetGame();
	void StartGame();
	void EndGame();
	void FinishGame();

	int m_moveStage[3];
	int m_timeStage[3];
private:
	int m_curStage;
};