#pragma once
#include "Enum.h"

class IMovable
{
public:
	virtual ~IMovable() = default;
	virtual void Move(Dir _dir) abstract;
};

