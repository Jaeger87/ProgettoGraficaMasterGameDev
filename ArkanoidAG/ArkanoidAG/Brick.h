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
	static Vec2* m_origin;
public:
	enum LIFEBRICK { FULL, HALF, DEAD };
	LIFEBRICK life;
	const float BWIDTH = 20;
	const float BHEIGHT = 10;
	void display(std::unique_ptr<DirectX::SpriteBatch>& i_spriteBatch) override;
	void setupTexture(Texture* i_texture, Vec2* i_origin) override;
	void Reset() override;
	bool isAlive();
	void hit();

};