#pragma once
#include "Vec2.h"

class Entity
{
protected:

	Vec2 position;

public:
	Entity(Vec2 _position);
	virtual void display() = 0;
};