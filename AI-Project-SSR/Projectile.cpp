#include "Projectile.h"

double const Projectile::DEG_TO_RAD = 0.0174533;
double const Projectile::RAD_TO_DEG = 57.2958;

Projectile::Projectile(Vector2f position, float speed, float rotation, float mWidth, float mHeight)
{
	m_position = position;

	m_rotation = rotation;
	if (!m_texture.loadFromFile("./Resources/Sprites/bullet_sprite.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	mapWidth = mWidth;
	mapHeight = mHeight;
	float x = cos(m_rotation * DEG_TO_RAD) * speed;
	float y = sin(m_rotation * DEG_TO_RAD) * speed;
	velocity = Vector2f(x, y);
	collider.setRadius(radius);
	collider.setPosition(sf::Vector2f(position.x, position.y));
	collider.setRotation(rotation);
	collider.setTexture(&m_texture);
	collider.setOrigin(sf::Vector2f(radius, radius));
}


Projectile::~Projectile()
{
}


void Projectile::update(float dt)
{
	m_position += velocity * dt;
	collider.setPosition(sf::Vector2f(m_position.x, m_position.y));
	if (m_position.x < -(collider.getRadius()))
	{
		m_position.x = mapWidth + (collider.getRadius());
	}
	else if (m_position.x - (collider.getRadius()) > mapWidth)
	{
		m_position.x = -(collider.getRadius());
	}
	else if (m_position.y < -(collider.getRadius()))
	{
		m_position.y = mapHeight + (collider.getRadius());
	}
	else if (m_position.y - (collider.getRadius()) > mapHeight)
	{
		m_position.y = -(collider.getRadius());
	}
}

void Projectile::render(sf::RenderWindow& window)
{
	window.draw(collider);
}
