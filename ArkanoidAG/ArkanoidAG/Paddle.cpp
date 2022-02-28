#include "pch.h"
#include "Paddle.h"

Texture* Paddle::m_texture;
Vec2* Paddle::m_origin;

Paddle::Paddle(Vec2* position, float length, float height) : Rect(position, length, height)
{

}

void Paddle::setupTexture(Texture* i_texture, Vec2* i_origin)
{
    m_texture = i_texture;
    m_origin = i_origin;
}

void Paddle::display(SpriteBatchAlias& i_spriteBatch, VertexDrawer& i_Drawer)
{
    RECT m_stretchRect;

    m_stretchRect.left = position->x;
    m_stretchRect.top = position->y;
    m_stretchRect.right = position->x + m_width;
    m_stretchRect.bottom = position->y + m_height;

    i_spriteBatch->Draw(m_texture->Get(), m_stretchRect, nullptr,
        DirectX::Colors::White);
}

void Paddle::getInput(float deltaX, Wall* leftWall, Wall* rightWall)
{
    if (position->x + deltaX <= leftWall->getInternalLimit() || position->x + deltaX + m_width >= rightWall->getInternalLimit())
        return;
    position->x += deltaX;
}

void Paddle::Reset()
{
    m_texture->Reset();
}