#include "pch.h"
#include "Entity.h"
#include <DirectXColors.h>

Entity::Entity(Vec2* _position):position(_position)
{

}

void Entity::display(std::unique_ptr<DirectX::SpriteBatch> & i_spriteBatch)
{
	i_spriteBatch->Draw(m_texture->Get(), *position, nullptr,
		DirectX::Colors::White, 0.f, *m_origin);
}


void Entity::setupTexture(Texture* i_texture, Vec2* i_origin)
{
	m_texture = i_texture;
	m_origin = i_origin;
}

void Entity::Reset()
{
	m_texture->Reset();
}
