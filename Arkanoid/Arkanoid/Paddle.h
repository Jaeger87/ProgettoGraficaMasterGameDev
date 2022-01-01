#pragma once
#include "Rect.h"

class Paddle : public Rect
{

private:
	const float height = 10;
public:

	Paddle(Vec2 position, float length);
	void display();
	void getInput(float newX);
};