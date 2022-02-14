#pragma once
using Vec2 = DirectX::SimpleMath::Vector2;
using Texture = Microsoft::WRL::ComPtr<ID3D12Resource>;
using Microsoft::WRL::ComPtr;

class Entity
{

protected:
	static Texture* m_texture;
	Vec2* position;
	static Vec2* m_origin;

public:
	Entity(Vec2* _position);
	virtual void display(DirectX::SpriteBatch* i_spriteBatch) = 0;
	static void setupTexture(Texture* i_texture, ComPtr<ID3D12Resource> &i_resource);
};