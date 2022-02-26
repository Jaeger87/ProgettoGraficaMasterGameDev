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
	void display(std::unique_ptr<DirectX::SpriteBatch>& i_spriteBatch) override;
	void setupTexture(Texture* i_texture, Vec2* i_origin) override;
	void getInput(float newX);
};