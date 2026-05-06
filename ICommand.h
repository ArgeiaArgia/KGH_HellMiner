#pragma once
class Object;
class ICommand
{
public:
	virtual ~ICommand() = default;
	virtual void Execute(Object* _object) abstract;
};