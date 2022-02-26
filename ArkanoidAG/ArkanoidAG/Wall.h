#pragma once
#include "Rect.h"


class Wall : public Rect
{
private:
	static Texture* m_texture;
	static Vec2* m_origin;

public:
	Wall(Vec2* _position, float _width, float _height);
	void display(std::unique_ptr<DirectX::SpriteBatch>& i_spriteBatch) override;
	void setupTexture(Texture* i_texture, Vec2* i_origin) override;
};