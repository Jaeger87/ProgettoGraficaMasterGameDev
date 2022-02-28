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
    Vec2 leftTop = Vec2(rect.position->x, rect.position->y);
    Vec2 rightTop = Vec2(rect.position->x + rect.m_width, rect.position->y);
    Vec2 leftBottom = Vec2(rect.position->x, rect.position->y + rect.m_height);
    Vec2 rightBottom = Vec2(rect.position->x + rect.m_width, rect.position->y + rect.m_height);

    boolean bottomCollision;
    boolean topCollision = false;
    boolean leftCollision;
    boolean rightCollision = false;



    bottomCollision = lineCircle(leftBottom, rightBottom, RECTCOLLISIONTYPE::WIDTH);
    if (!bottomCollision)
        topCollision = lineCircle(leftTop, rightTop, RECTCOLLISIONTYPE::WIDTH);

    if (topCollision || bottomCollision)
        velocity.y *= -1;

    leftCollision = lineCircle(leftTop, leftBottom, RECTCOLLISIONTYPE::LENGTH);
    if (!leftCollision)
        rightCollision = lineCircle(rightTop, rightBottom, RECTCOLLISIONTYPE::LENGTH);

    if (leftCollision || rightCollision)
        velocity.x *= -1;

    return topCollision || bottomCollision || leftCollision || rightCollision;
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

  
    
    // CheckWalls
    if (position->x - radius <= leftWall.getInternalLimit() || position->x + radius >= rightWall.getInternalLimit())
    {
        cooldown = false;
        velocity.x *= -1;
    }
    
    if (position->y - radius <= upWall.getInternalLimit())
    {
        cooldown = false;
        velocity.y *= -1;
    }
    /*
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
    RECT m_stretchRect;

    m_stretchRect.left = position->x - radius;
    m_stretchRect.top = position->y - radius;
    m_stretchRect.right = position->x + radius;
    m_stretchRect.bottom = position->y + radius;

    i_spriteBatch->Draw(m_texture->Get(), m_stretchRect, nullptr,
        DirectX::Colors::White);
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
