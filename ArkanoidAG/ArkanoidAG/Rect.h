#pragma once
#include "Entity.h"

class Rect : public Entity
{
protected:
	float m_width;
	float m_height;
	
public:
	friend class Sphere;
	Rect(Vec2* _position, float _width, float _height);
	virtual void display(SpriteBatchAlias& i_spriteBatch, VertexDrawer& i_Drawer) = 0;
};