#pragma once
#include "ICommand.h"
#include "Enum.h"

class MoveCommand : public ICommand
{
public:
	MoveCommand(Dir _dir);
	virtual void Execute(Object* _object) override;
private:
	Dir m_dir;
};