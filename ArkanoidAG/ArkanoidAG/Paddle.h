#pragma once
#include "Rect.h"
#include "Wall.h"

class Wall;


class Paddle : public Rect
{

private:
	static Texture* m_texture;
	const float height = 16;

public:
	Paddle(Vec2* position, float length, float height);
	void setPosition(float i_x, float i_y);
	void display(SpriteBatchAlias& i_spriteBatch, VertexDrawer& i_Drawer) override;
	static void setupTexture(Texture* i_texture);
	static void Reset();
	void getInput(float deltaX, Wall* leftWall, Wall* rightWall);
};