#include "Missile.h"



Missile::Missile(Vector2f position, float speed, float rotation, float mWidth, float mHeight) 
	: Projectile(position, speed, rotation, mWidth, mHeight)
{
	auto texture = sf::Texture();
	if (!texture.loadFromFile("./Resources/Sprites/Rocket_sprite.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	else
	{
		m_texture = std::make_shared<sf::Texture>(std::move(texture));
	}
	collider.setTexture(m_texture.get(), true);
	collider.setRadius(radius);
}


Missile::~Missile()
{
}

void Missile::update(float dt, Vector2f target)
{
	auto desired = Vector2f(target - m_position).normalise() * m_speed;

	auto steering = desired - velocity;

	velocity += steering;
	m_rotation = getOrientation(velocity);
	Projectile::update(dt);
}
