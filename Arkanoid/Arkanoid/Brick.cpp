#include "pch.h"
#include "Brick.h"

Color Brick::ColorFullLife = { { { 1.000000000f, 0.05f, 1.000000000f, 1.000000000f } } };

void Brick::display()
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
