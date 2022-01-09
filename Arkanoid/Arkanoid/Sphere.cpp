#include "pch.h"
#include "Sphere.h"


Color Sphere::sphereColor = { { { 0.1f, 1.000000000f, 0.1f, 1.000000000f } } };


bool Sphere::checkRectCollision(Rect& rect)
{
	return false;
}

bool Sphere::lineCircle(Vec2& point1, Vec2& point2, RECTCOLLISIONTYPE type)
{
	return false;
}

bool Sphere::pointCircle(Vec2& point)
{
	return false;
}

bool Sphere::linePoint(Vec2& point1, Vec2& point2, float lineLen, Vec2& pointX)
{
	return false;
}

Sphere::Sphere(Vec2 _position) : Entity(_position)
{

}

void Sphere::update(Paddle& paddle, Brick* bricks, int bricksLength, Wall& leftWall, Wall& upWall, Wall& rightWall)
{
    position += velocity;

    /*
    
    // CheckWalls
    if (position.x - radius <= 0 || position.x + radius >= processing.width)
    {
        cooldown = false;
        velocity.x *= -1;
    }
    
    if (position.y - radius <= 0)
    {
        cooldown = false;
        velocity.y *= -1;
    }

    if (velocity.y + radius >= processing.height)
        alive = false;

    */
    if (!cooldown && checkRectCollision(paddle))
    {
        cooldown = true;
    }

    for (int brickIndex = 0; brickIndex < bricksLength; brickIndex++) {
        if (bricks[brickIndex].isAlive() && checkRectCollision(bricks[brickIndex]))
        {
            bricks[brickIndex].hit();
            cooldown = false;
        }

    }
}

void Sphere::display(DirectX::SpriteBatch *i_spriteBatch)
{
    i_spriteBatch->Draw(m_texture->Get(), position, nullptr,
        sphereColor, 0.f, m_origin, 0.75f);
}
