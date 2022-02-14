#include "pch.h"
#include "Brick.h"

Color Brick::ColorFullLife = { { { 0.1f, 1.000000000f, 0.1f, 1.000000000f } } };
Color Brick::ColorHalfLife = { { { 1.000000000f, 0.1f, 0.1f, 1.000000000f } } };

void Brick::display(DirectX::SpriteBatch* i_spriteBatch)
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
