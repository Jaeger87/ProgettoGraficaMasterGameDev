#include "pch.h"
#include "Entity.h"

Entity::Entity(Vec2 _position):position(_position)
{
}

Texture* Entity::m_texture;
void Entity::setupTexture(Texture* i_texture)
{
	Entity::m_texture = i_texture;
}
