#include "pch.h"
#include "Wall.h"


Color Wall::m_Color = { { { 1.000000000f, 0.1f, 0.1f, 1.000000000f } } };


Wall::Wall(Vec2* _position, float _width, float _height) : Rect(_position, _width,_height)
{

}

void Wall::display(SpriteBatchAlias& i_spriteBatch, VertexDrawer& i_Drawer)
{	
	DirectX::VertexPositionColor v1(Vec2(position->x, position->y), m_Color);
	DirectX::VertexPositionColor v2(Vec2(position->x + m_width, position->y), m_Color);
	DirectX::VertexPositionColor v3(Vec2(position->x + m_width, position->y + m_height), m_Color);
	DirectX::VertexPositionColor v4(Vec2(position->x, position->y + m_height), m_Color);
	i_Drawer->DrawQuad(v1, v2, v3, v4);	
}