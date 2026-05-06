#pragma once
#include <vector>
#include "Object.h"

class Scene
{
public:
	virtual ~Scene();
public:
	virtual void Init();
	virtual void Update();
	virtual void Render() const;
protected:
	std::vector<Object*> objects;
};