#pragma once
using Vec2 = DirectX::SimpleMath::Vector2;
using Texture = Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>;
using Microsoft::WRL::ComPtr;

class Entity
{

protected:
	Texture* m_texture;
	Vec2* position;
	static Vec2* m_origin;

public:
	Entity(Vec2* _position);
	virtual void display(DirectX::SpriteBatch* i_spriteBatch) = 0;
	void setupTexture(Texture* i_texture, ComPtr<ID3D11ShaderResourceView> &i_resource);
	void Reset();
};