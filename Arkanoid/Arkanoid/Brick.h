#pragma once
#include "Rect.h"
#include <wrl.h>

#include <d3d11_3.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <exception>
#include <iterator>
#include <memory>
#include <stdexcept>

#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "WICTextureLoader.h"

using Color = DirectX::XMVECTORF32;

class Brick : public Rect
{
private:
	static Color ColorFullLife;
	static Color ColorHalfLife;
public:
	enum LIFEBRICK { FULL, HALF, DEAD };
	LIFEBRICK life;
	const float BWIDTH = 20;
	const float BHEIGHT = 10;
	void display(DirectX::SpriteBatch* i_spriteBatch) override;
	bool isAlive();
	void hit();

};