#include "pch.h"
#include "Paddle.h"

Paddle::Paddle(Vec2* position, float length) : Rect(position, length, height)
{
}

void Paddle::display(DirectX::SpriteBatch* i_spriteBatch)
{
}

void Paddle::getInput(float newX)
{
}
