#pragma once
#include "Rect.h"
#include <wrl.h>

#include <d3d11_3.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include <DirectXColors.h>


#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "WICTextureLoader.h"

class Brick : public Rect
{
private:
	static Color ColorFullLife;
	static Color ColorHalfLife;
	static Texture* m_texture_FullLife;
	static Texture* m_texture_HalfLife;
public:
	static const int BWIDTH = 32;
	static const int BHEIGHT = 16;
	enum LIFEBRICK { FULL, HALF, DEAD };
	LIFEBRICK life;
	Brick(Vec2* position, LIFEBRICK i_life);
	void display(SpriteBatchAlias& i_spriteBatch, VertexDrawer& i_Drawer) override;
	static void setupTexture(Texture* i_FullLifeTexture, Texture* i_HalfLifeTexture);
	static void Reset();
	bool isAlive();
	void hit();

};