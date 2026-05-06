#include "MoveCommand.h"
#include "IMovable.h"
#include "Object.h"

MoveCommand::MoveCommand(Dir _dir) : m_dir(_dir)
{
}

void MoveCommand::Execute(Object* _object)
{
	IMovable* mover = dynamic_cast<IMovable*>(_object);
	if (mover)
	{
		mover->Move(m_dir);
	}
}
