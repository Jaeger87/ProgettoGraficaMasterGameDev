#pragma once
#include "Rect.h"

class Paddle : public Rect
{

private:
	static Texture* m_texture;
	static Vec2* m_origin;
	const float height = 16;

public:
	Paddle(Vec2* position, float length, float height);
	void display(SpriteBatchAlias& i_spriteBatch) override;
	static void setupTexture(Texture* i_texture, Vec2* i_origin);
	static void Reset();
	void getInput(float newX);
};