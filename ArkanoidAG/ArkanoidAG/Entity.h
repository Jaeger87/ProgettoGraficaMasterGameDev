#pragma once
using Vec2 = DirectX::SimpleMath::Vector2;
using Texture = Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>;
using Microsoft::WRL::ComPtr;
using Color = DirectX::XMVECTORF32;

class Entity
{

protected:
	Texture* m_texture;
	Vec2* position;
	Vec2* m_origin;

public:
	Entity(Vec2* _position);
	virtual void display(std::unique_ptr<DirectX::SpriteBatch> & i_spriteBatch);
	void setupTexture(Texture* i_texture, Vec2* i_origin);
	void Reset();
};