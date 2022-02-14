#pragma once
#include "Entity.h"
#include "Paddle.h"
#include "Brick.h"
#include "Wall.h"

class Sphere : Entity 
{
private:
	static Color sphereColor;
	Vec2 velocity;
	const float radius = 12;
	const float SQUARERADIUS = 12 ^ 2;
	bool alive = true;
	bool cooldown = false;
	enum class RECTCOLLISIONTYPE { LENGTH, WIDTH };
	bool checkRectCollision(Rect& rect);
	bool lineCircle(Vec2& point1, Vec2& point2, RECTCOLLISIONTYPE type);
	bool pointCircle(Vec2& point);
	bool linePoint(Vec2& point1, Vec2& point2, float lineLen, Vec2& pointX);
public:
	Sphere(Vec2* _position);
	void update(Paddle& paddle, Brick* bricks, int bricksLength, Wall& leftWall, Wall& upWall, Wall& rightWall);
	void display(DirectX::SpriteBatch* i_spriteBatch) override;
	
};