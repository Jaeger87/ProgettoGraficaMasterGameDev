#include "pch.h"
#include "Brick.h"

Color Brick::ColorFullLife = { { { 0.1f, 1.000000000f, 0.1f, 1.000000000f } } };
Color Brick::ColorHalfLife = { { { 1.000000000f, 0.1f, 0.1f, 1.000000000f } } };

Texture* Brick::m_texture_FullLife;
Texture* Brick::m_texture_HalfLife;
Vec2* Brick::m_origin;

void Brick::setupTexture(Texture* i_FullLifeTexture, Texture* i_HalfLifeTexture, Vec2* i_origin)
{
    m_texture_FullLife = i_FullLifeTexture;
    m_texture_HalfLife = i_HalfLifeTexture;
    m_origin = i_origin;
}

void Brick::display(SpriteBatchAlias& i_spriteBatch, VertexDrawer& i_Drawer)
{
    if (!isAlive())
        return;

    if (life == LIFEBRICK::HALF)
    {
        i_spriteBatch->Draw(m_texture_HalfLife->Get(), *position, nullptr,
            DirectX::Colors::White, 0.f, *m_origin, 0.5);
        return;
    }

    i_spriteBatch->Draw(m_texture_FullLife->Get(), *position, nullptr,
        DirectX::Colors::White, 0.f, *m_origin, 0.5);
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
