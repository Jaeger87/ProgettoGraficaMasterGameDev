#pragma once
using Vec2 = DirectX::SimpleMath::Vector2;
using Texture = Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>;
using Microsoft::WRL::ComPtr;
using Color = DirectX::XMVECTORF32;
using SpriteBatchAlias = std::unique_ptr<DirectX::SpriteBatch>;
using VertexDrawer = std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>;

class Entity
{

protected:
	Vec2* position;
	Vec2* m_origin;

public:
	Entity(Vec2* _position);
	virtual void display(SpriteBatchAlias& i_spriteBatch, VertexDrawer& i_Drawer) = 0;
};