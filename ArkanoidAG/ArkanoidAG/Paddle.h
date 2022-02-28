#pragma once
#include "Rect.h"
#include "Wall.h"

class Wall;


class Paddle : public Rect
{

private:
	static Texture* m_texture;
	static Vec2* m_origin;
	const float height = 16;

public:
	Paddle(Vec2* position, float length, float height);
	void display(SpriteBatchAlias& i_spriteBatch, VertexDrawer& i_Drawer) override;
	static void setupTexture(Texture* i_texture, Vec2* i_origin);
	static void Reset();
	void getInput(float deltaX, Wall* leftWall, Wall* rightWall);
};