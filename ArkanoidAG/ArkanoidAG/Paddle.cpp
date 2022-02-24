#include "pch.h"
#include "Paddle.h"

Texture* Paddle::m_texture;
Vec2* Paddle::m_origin;

Paddle::Paddle(Vec2* position, float length) : Rect(position, length, height)
{
}

void Paddle::setupTexture(Texture* i_texture, Vec2* i_origin)
{
    m_texture = i_texture;
    m_origin = i_origin;
}

void Paddle::display(DirectX::SpriteBatch* i_spriteBatch)
{
}

void Paddle::getInput(float newX)
{
}
