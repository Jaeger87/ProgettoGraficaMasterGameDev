#pragma once
#include "Rect.h"

class Paddle : public Rect
{

private:
	const float height = 10;
public:

	Paddle(Vec2* position, float length);
	void display(DirectX::SpriteBatch* i_spriteBatch) override;
	void getInput(float newX);
};