#pragma once
#include<vector>
#include "Enum.h"
class ICommand;
struct MoveKey {
	int vk;
	Dir dir;
};
struct ActionKey 
{
	int vk;
	Action act;
};
class InputHandler
{
public: 
	InputHandler();
public:
	ICommand* HandleInput();
	std::vector<MoveKey> m_moveKeys;
	std::vector<ActionKey> m_actionKeys;
};