#include "pch.h"
#include "Sphere.h"


Color Sphere::sphereColor = { { { 0.1f, 1.000000000f, 0.1f, 1.000000000f } } };


Texture* Sphere::m_texture;
Vec2* Sphere::m_origin;

Sphere::Sphere(Vec2* _position) : Entity(_position)
{
    velocity = Vec2(1.0f, 1.0f);
}

bool Sphere::checkRectCollision(Rect& rect)
{
	return false;
}

bool Sphere::lineCircle(Vec2& point1, Vec2& point2, RECTCOLLISIONTYPE type)
{
    // is either end INSIDE the circle?
// if so, return true immediately
    boolean inside1 = pointCircle(point1);
    boolean inside2 = pointCircle(point2);
    if (inside1 || inside2) return true;

    // get length of the line
    float len = type == RECTCOLLISIONTYPE::WIDTH ? abs(point1.x - point2.x) :
        abs(point1.y - point2.y);

    // get dot product of the line and circle
    float dot = (((position->x - point1.x) * (point2.x - point1.x)) +
        ((position->y - point1.y) * (point2.y - point1.y))) / pow(len, 2);

    // find the closest point on the line
    float closestX = point1.x + (dot * (point2.x - point1.x));
    float closestY = point1.y + (dot * (point2.y - point1.y));

    Vec2 closestPoint = Vec2(closestX, closestY);
    // is this point actually on the line segment?
    // if so keep going, but if not, return false
    boolean onSegment = linePoint(point1, point2, len, closestPoint);
    if (!onSegment) return false;

    // get distance to closest point
    float distX = closestX - position->x;
    float distY = closestY - position->y;
    float squareDistance = (distX * distX) + (distY * distY);

    if (squareDistance <= SQUARERADIUS) {
        return true;
    }
    return false;
}

bool Sphere::pointCircle(Vec2& point)
{
    float distX = point.x - position->x;
    float distY = point.y - position->y;
    float squareDistance = (distX * distX) + (distY * distY);

    // if the distance is less than the circle's
    // radius the point is inside!
    if (squareDistance <= SQUARERADIUS) {
        return true;
    }
    return false;
}

bool Sphere::linePoint(Vec2& point1, Vec2& point2, float lineLen, Vec2& pointX)
{
    // get distance from the point to the two ends of the line
    
    float d1 = Vec2::Distance(point1, pointX);
    float d2 = Vec2::Distance(point2, pointX);

    // since floats are so minutely accurate, add
    // a little buffer zone that will give collision
    float buffer = 0.1f;    // higher # = less accurate

    // if the two distances are equal to the line's
    // length, the point is on the line!
    // note we use the buffer here to give a range,
    // rather than one #
    if (d1 + d2 >= lineLen - buffer && d1 + d2 <= lineLen + buffer) {
        return true;
    }
    return false;
}



void Sphere::update(Paddle& paddle, Brick* bricks, int bricksLength, Wall& leftWall, Wall& upWall, Wall& rightWall)
{
    *position += velocity;

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

void Sphere::setupTexture(Texture* i_texture, Vec2* i_origin)
{
    m_texture = i_texture;
    m_origin = i_origin;
}

void Sphere::display(SpriteBatchAlias& i_spriteBatch, VertexDrawer& i_Drawer)
{
    i_spriteBatch->Draw(m_texture->Get(), *position, nullptr,
        DirectX::Colors::White, 0.f, *m_origin, 0.5);
}

/*
void Sphere::display(DirectX::SpriteBatch *i_spriteBatch)
{
    
    i_spriteBatch->Draw(m_texture->Get(), position, nullptr,
        sphereColor, 0.f, m_origin, 0.75f);
    
}
*/

void Sphere::Reset()
{
    m_texture->Reset();
}
