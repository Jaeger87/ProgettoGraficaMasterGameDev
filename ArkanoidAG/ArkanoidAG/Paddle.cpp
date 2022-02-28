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
    i_spriteBatch->Draw(m_texture->Get(), *position, nullptr,
        DirectX::Colors::White, 0.f, *m_origin);
}

void Paddle::getInput(float deltaX, Wall* leftWall, Wall* rightWall)
{
    //if(position->x + deltaX < leftWall.)
    position->x += deltaX;
}

void Paddle::Reset()
{
    m_texture->Reset();
}