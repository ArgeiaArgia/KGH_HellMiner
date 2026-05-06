#pragma once
#include "GameManager.h"
#include "Object.h"
#include "MapManager.h"

class CompleteUI : public Object
{
public:
	CompleteUI(Position pos);
	virtual ~CompleteUI() = default;

public:
	virtual void Update() override;
	virtual void Render() const override;
private:
	void DrawWord(wstring word) const;
private:
	wstring m_chapi[13]; //차피
	wstring m_blue[5]; //파랑 피크민
	wstring star; //별
	wstring num; // 보여줄 숫자
	MapManager* m_mapManager;
	GameManager* m_gm;
	const int width = 1, height = 6;
};

