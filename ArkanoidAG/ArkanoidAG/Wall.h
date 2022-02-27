#pragma once
#include "Rect.h"


class Wall : public Rect
{
private:
	static Texture* m_texture;
	static Vec2* m_origin;
	static Color m_Color;


public:
	enum WALLTYPE { LEFT, UP, RIGHT };
	WALLTYPE m_WallType;
	Wall(Vec2* _position, float _width, float _height, WALLTYPE _wallType);
	void display(SpriteBatchAlias& i_spriteBatch, VertexDrawer& i_Drawer) override;
	int getInternalLimit();
};