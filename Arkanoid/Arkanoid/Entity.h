#pragma once

using Vec2 = DirectX::SimpleMath::Vector2;
using Texture = Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>;
class Entity
{

protected:
	static Texture *m_texture;
	Vec2 position;

public:
	Entity(Vec2 _position);
	virtual void display() = 0;
	static void Entity::setupTexture(Texture* i_texture);
};