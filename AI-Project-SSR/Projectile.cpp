#include "Projectile.h"

Projectile::Projectile(Vector2f position, float speed)
{
	m_position = position;

	m_rotation = 0;
	float x = cos(m_rotation * DEG_TO_RAD) * speed;
	float y = sin(m_rotation * DEG_TO_RAD) * speed;
	velocity = Vector2f(x, y);
}


Projectile::~Projectile()
{
}


void Projectile::update(float dt)
{
	m_position += velocity;
}