#include "pch.h"
#include "Brick.h"

Texture* Brick::m_texture_FullLife;
Texture* Brick::m_texture_HalfLife;

Brick::Brick(Vec2* position, LIFEBRICK i_life, ScoreManager* i_scoreManager) : Rect(position, BWIDTH, BHEIGHT)
{
    life = i_life;
    m_ScoreManager = i_scoreManager;
    if (life == LIFEBRICK::FULL)
        m_scoreValue = 200;
    else
        m_scoreValue = 100;
}

void Brick::setupTexture(Texture* i_FullLifeTexture, Texture* i_HalfLifeTexture)
{
    m_texture_FullLife = i_FullLifeTexture;
    m_texture_HalfLife = i_HalfLifeTexture;
}


void Brick::display(SpriteBatchAlias& i_spriteBatch, VertexDrawer& i_Drawer)
{
    if (!isAlive())
        return;
    RECT m_stretchRect;

    m_stretchRect.left = position->x;
    m_stretchRect.top = position->y;
    m_stretchRect.right = position->x + m_width;
    m_stretchRect.bottom = position->y + m_height;


    if (life == LIFEBRICK::HALF)
    {
        i_spriteBatch->Draw(m_texture_HalfLife->Get(), m_stretchRect, nullptr,
            DirectX::Colors::White);
        return;
    }

    i_spriteBatch->Draw(m_texture_FullLife->Get(), m_stretchRect, nullptr,
        DirectX::Colors::White);
}

bool Brick::isAlive()
{
    return life != LIFEBRICK::DEAD;
}

void Brick::hit()
{
    if (life == LIFEBRICK::DEAD)
        return;

    if (life == LIFEBRICK::FULL)
        life = LIFEBRICK::HALF;
    else
    {
        life = LIFEBRICK::DEAD;
        m_ScoreManager->addPoints(m_scoreValue);
    }
        
}

void Brick::Reset()
{
    m_texture_HalfLife->Reset();
    m_texture_FullLife->Reset();
}
