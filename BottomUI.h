#pragma once
#include "Object.h"
class BottomUI : public Object
{
public:
	BottomUI(Position pos);
	virtual ~BottomUI() = default;

public:
	virtual void Update() override;
	virtual void Render() const override;
};

