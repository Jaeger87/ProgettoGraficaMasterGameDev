#pragma once
#include "Entity.h"
#include "Paddle.h"
#include "Brick.h"
#include "Wall.h"

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
	Sphere(Vec2 _position);
	void update(Paddle& paddle, Brick* bricks, int bricksLength, Wall& leftWall, Wall& upWall, Wall& rightWall);
	
};