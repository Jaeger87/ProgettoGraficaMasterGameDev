#include "pch.h"
#include "Brick.h"

Color Brick::ColorFullLife = { { { 0.1f, 1.000000000f, 0.1f, 1.000000000f } } };
Color Brick::ColorHalfLife = { { { 1.000000000f, 0.1f, 0.1f, 1.000000000f } } };

Texture* Brick::m_texture_FullLife;
Texture* Brick::m_texture_HalfLife;
Vec2* Brick::m_origin;

void Brick::setupTexture(Texture* i_texture, Vec2* i_origin)
{
    m_texture_FullLife = &i_texture[0];
    m_texture_HalfLife = &i_texture[1];
    m_origin = i_origin;
}

void Brick::display(std::unique_ptr<DirectX::SpriteBatch>& i_spriteBatch)
{
    
}

bool Brick::isAlive()
{
    return life != LIFEBRICK::DEAD;
}

void Brick::hit()
{
    if (life == LIFEBRICK::FULL)
        life = LIFEBRICK::HALF;
    else
        life = LIFEBRICK::DEAD;
}

void Brick::Reset()
{
    m_texture_HalfLife->Reset();
    m_texture_FullLife->Reset();
}
