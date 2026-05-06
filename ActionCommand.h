#pragma once
#include "ICommand.h"
#include "Enum.h"

class ActionCommand : public ICommand
{
public:
	ActionCommand(Action _act);
	virtual void Execute(Object* _object) override;
private:
	Action m_act;
};

