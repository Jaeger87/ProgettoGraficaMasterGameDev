#include "pch.h"
#include "Sphere.h"

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

void Sphere::update(Paddle paddle, Brick* bricks, int bricksLength)
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
