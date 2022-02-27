#include "pch.h"
#include "Wall.h"


Color Wall::m_Color;

Wall::Wall(Vec2* _position, float _width, float _height) : Rect(_position, _width,_height)
{

}

void Wall::setupTexture(Texture* i_texture, Vec2* i_origin)
{

}

void Wall::display(std::unique_ptr<DirectX::SpriteBatch>& i_spriteBatch)
{
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
	
	DirectX::VertexPositionColor v1(Vec2(position->x - m_width / 2, position->y - m_height / 2), m_Color);
	DirectX::VertexPositionColor v2(Vec2(position->x + m_width / 2, position->y - m_height / 2), m_Color);
	DirectX::VertexPositionColor v3(Vec2(position->x + m_width / 2, position->y + m_height / 2), m_Color);
	DirectX::VertexPositionColor v4(Vec2(position->x - m_width / 2, position->y + m_height / 2), m_Color);
	m_batch->DrawQuad(v1, v2, v3, v4);
	
}

void Wall::Reset()
{

}