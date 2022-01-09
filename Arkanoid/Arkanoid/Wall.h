#pragma once
#include "Rect.h"


class Wall : public Rect
{
public:
	Wall(Vec2 _position, float _width, float _height);
	void display() override;
};