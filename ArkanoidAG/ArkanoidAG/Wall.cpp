#include "pch.h"
#include "Wall.h"

Texture* Wall::m_texture;
Vec2* Wall::m_origin;

Wall::Wall(Vec2* _position, float _width, float _height) : Rect(_position, _width,_height)
{

}

void Wall::setupTexture(Texture* i_texture, Vec2* i_origin)
{
    m_texture = i_texture;
    m_origin = i_origin;
}

void Wall::display(DirectX::SpriteBatch* i_spriteBatch)
{
}
