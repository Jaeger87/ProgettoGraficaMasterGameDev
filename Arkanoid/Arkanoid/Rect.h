#pragma once
#include "Entity.h"

class Rect : Entity
{
protected:
	float width;
	float height;
public:
	Rect(Vec2 _position, float _width, float _height);
	virtual void display() = 0;
};