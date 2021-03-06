#pragma once
#include "Entity.h"
#include "Paddle.h"
#include "Brick.h"
#include "Wall.h"

class Sphere : public Entity
{
private:
	static Texture* m_texture;
	static Color sphereColor;
	Vec2 velocity;
	const float radius = 8;
	const float SQUARERADIUS = 8 ^ 2;
	bool alive = true;
	bool cooldown = false;
	enum class RECTCOLLISIONTYPE { LENGTH, WIDTH };
	//bool checkRectCollision(Rect& rect);
	bool lineCircle(Vec2& point1, Vec2& point2, RECTCOLLISIONTYPE type);
	bool pointCircle(Vec2& point);
	bool linePoint(Vec2& point1, Vec2& point2, float lineLen, Vec2& pointX);
	float deathLine;
public:
	Sphere(Vec2* _position, float displayHeight);
	void resetSphere(float i_x, float i_y);
	bool checkRectCollision(Rect& rect);
	void update(Paddle& paddle, Brick** bricks, int bricksLength, Wall& leftWall, Wall& upWall, Wall& rightWall);
	void display(SpriteBatchAlias& i_spriteBatch, VertexDrawer& i_Drawer) override;
	bool isAlive();
	static void Reset();
	static void setupTexture(Texture* i_texture);
	
};