#pragma once
#include "Entity.h"
#include "Paddle.h"
#include "Brick.h"

class Sphere : Entity 
{
private:
	Vec2 velocity;
	const float radius = 11;
	const float SQUARERADIUS = 11 ^ 2;
	bool alive = true;
	bool cooldown = false;
	enum RECTCOLLISIONTYPE { LENGTH, WIDTH };
	bool checkRectCollision(Rect& rect);
	bool lineCircle(Vec2& point1, Vec2& point2, RECTCOLLISIONTYPE type);
	bool pointCircle(Vec2& point);
	bool linePoint(Vec2& point1, Vec2& point2, float lineLen, Vec2& pointX);
public:
	void update(Paddle paddle, Brick* bricks, int bricksLength);
	
};