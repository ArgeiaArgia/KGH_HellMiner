#include "InputHandler.h"
#include "MoveCommand.h"
#include "ActionCommand.h"
#include <Windows.h>

InputHandler::InputHandler()
{
	m_moveKeys.push_back({ 'W', Dir::UP });
	m_moveKeys.push_back({ 'A', Dir::LEFT });
	m_moveKeys.push_back({ 'S', Dir::DOWN });
	m_moveKeys.push_back({ 'D', Dir::RIGHT });

	m_moveKeys.push_back({ VK_UP, Dir::UP });
	m_moveKeys.push_back({ VK_LEFT, Dir::LEFT });
	m_moveKeys.push_back({ VK_DOWN, Dir::DOWN });
	m_moveKeys.push_back({ VK_RIGHT, Dir::RIGHT });

	m_actionKeys.push_back({ 'E', Action::DIG });
	m_actionKeys.push_back({ 'Q', Action::FLAG });
	m_actionKeys.push_back({ VK_SPACE, Action::Select });
	m_actionKeys.push_back({ 'R', Action::RESET });
	m_actionKeys.push_back({ VK_ESCAPE, Action::TITLE});
}

ICommand* InputHandler::HandleInput()
{
	for (auto& key : m_moveKeys) {
		bool isDown = (GetAsyncKeyState(key.vk) & 0x0001) != 0;
		if (isDown)
			return new MoveCommand(key.dir);
	}
	for (auto& key : m_actionKeys) {
		bool isDown = (GetAsyncKeyState(key.vk) & 0x0001) != 0;
		if (isDown)
			return new ActionCommand(key.act);
	}

	return nullptr;
}
