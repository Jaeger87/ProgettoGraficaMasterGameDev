#include "pch.h"
#include "Entity.h"


Texture* Entity::m_texture;
Vec2 Entity::m_origin;

Entity::Entity(Vec2 _position):position(_position)
{
}


void Entity::setupTexture(Texture* i_texture, ComPtr<ID3D11Resource> &i_resource)
{
	Entity::m_texture = i_texture;

	ComPtr<ID3D11Texture2D> sprite;
	DX::ThrowIfFailed(i_resource.As(&sprite));

	CD3D11_TEXTURE2D_DESC spriteDesc;
	sprite->GetDesc(&spriteDesc);

	m_origin.x = float(spriteDesc.Width / 2);
	m_origin.y = float(spriteDesc.Height / 2);

}
