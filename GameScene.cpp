#include "GameScene.h"
#include "Player.h"
#include "ICommand.h"
#include "TopUI.h"
#include "SideUI.h"
#include "BottomUI.h"
#include "CompleteUI.h"
#include "Mci.h"

GameScene::GameScene()
{
	TopUI* tUi = new TopUI({ 0,0 });
	objects.push_back(tUi);
	SideUI* sUi = new SideUI({ MAP_WIDTH,UI_HEIGHT });
	objects.push_back(sUi);
	BottomUI* bUi = new BottomUI({ 0,40 });
	objects.push_back(bUi);

	Map* map = new Map({ MARGIN, UI_HEIGHT });
	objects.push_back(map);

	CompleteUI* cUi = new CompleteUI({ MARGIN, UI_HEIGHT });
	objects.push_back(cUi);

	Player* player = new Player({ 0, UI_HEIGHT });
	objects.push_back(player);
}

void GameScene::Update()
{
	ICommand* m_cmd;
	m_cmd = m_inputHandler.HandleInput();
	for (auto obj : objects)
	{
		if (m_cmd != nullptr)
			m_cmd->Execute(obj);
		obj->Update();
	}
	SAFE_DELETE(m_cmd);
}
