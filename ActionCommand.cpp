#include "ActionCommand.h"
#include "IActionable.h"
#include "Object.h"

ActionCommand::ActionCommand(Action _act) : m_act(_act)
{
}

void ActionCommand::Execute(Object* _object)
{
	IActable* actor = dynamic_cast<IActable*>(_object);
	if (actor)
	{
		actor->Act(m_act);
	}
}
