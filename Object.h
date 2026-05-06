#pragma once
#include "Position.h"

class Object
{
public:
	Object(Position pos);
	virtual ~Object() = default;
public:
	virtual void Init();
	virtual void Render() const abstract;
	virtual void Update() abstract;
protected:
	Position m_pos;
};