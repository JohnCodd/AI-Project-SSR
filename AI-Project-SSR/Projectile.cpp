#include "Projectile.h"

double const Projectile::DEG_TO_RAD = 0.0174533;
double const Projectile::RAD_TO_DEG = 57.2958;

Projectile::Projectile(Vector2f position, float speed, float rotation, float mWidth, float mHeight)
{
	m_position = position;

	m_rotation = rotation;
	auto texture = sf::Texture();
	if (!texture.loadFromFile("./Resources/Sprites/bullet_sprite.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	else
	{
		m_texture = std::make_shared<sf::Texture>(std::move(texture));
	}
	mapWidth = mWidth;
	mapHeight = mHeight;
	float x = cos(m_rotation * DEG_TO_RAD) * speed;
	float y = sin(m_rotation * DEG_TO_RAD) * speed;
	m_speed = speed;
	velocity = Vector2f(x, y);
	collider.setRadius(radius);
	collider.setPosition(sf::Vector2f(position.x, position.y));
	collider.setRotation(rotation);
	collider.setOrigin(sf::Vector2f(radius, radius));
	collider.setTexture(m_texture.get(), true);
	rect.setTexture(m_texture.get());
	rect.setPosition(sf::Vector2f(position.x, position.y));
	rect.setRotation(rotation);
	rect.setSize(sf::Vector2f(radius * 2, radius * 2));
	rect.setOrigin(sf::Vector2f(radius, radius));
}


Projectile::~Projectile()
{
}


void Projectile::update(float dt, Map& m)
{
	if (active)
	{
		m_position += velocity * dt;
		collider.setPosition(sf::Vector2f(m_position.x, m_position.y));
		collider.setRotation(m_rotation);
		rect.setPosition(sf::Vector2f(m_position.x, m_position.y));
		rect.setRotation(m_rotation);
		if (m_position.x < -(collider.getRadius()))
		{
			active = false;
		}
		else if (m_position.x - (collider.getRadius()) > mapWidth)
		{
			active = false;
		}
		else if (m_position.y < -(collider.getRadius()))
		{
			active = false;
		}
		else if (m_position.y - (collider.getRadius()) > mapHeight)
		{
			active = false;
		}
		sf::Vector2f tileLocation = sf::Vector2f(floor(m_position.x / 100), floor(m_position.y / 100));
		if (m.getTile(tileLocation)->getWall())
		{
			active = false;
		}
	}
}

void Projectile::render(sf::RenderWindow& window)
{
	if (active)
	{
		window.draw(collider);
	}
	//window.draw(rect);
}
