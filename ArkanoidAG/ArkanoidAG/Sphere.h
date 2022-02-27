#pragma once
#include "Entity.h"
#include "Paddle.h"
#include "Brick.h"
#include "Wall.h"

class Sphere : public Entity
{
private:
	static Texture* m_texture;
	static Vec2* m_origin;
	static Color sphereColor;
	Vec2 velocity;
	const float radius = 16;
	const float SQUARERADIUS = 16 ^ 2;
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
	void display(std::unique_ptr<DirectX::SpriteBatch>& i_spriteBatch) override;
	void Reset() override;
	void setupTexture(Texture* i_texture, Vec2* i_origin) override;
	
};