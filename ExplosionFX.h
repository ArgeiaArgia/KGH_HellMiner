#pragma once
#include "Object.h"
class ExplosionFX : public Object
{
public:
	ExplosionFX(Position _pos);
	void Render() const override;
	void Update() override;
private:
};