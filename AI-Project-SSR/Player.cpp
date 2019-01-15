#include "Player.h"
#include <random>
#include <iostream>

double const Player::DEG_TO_RAD = 0.0174533;

Player::Player(double mWidth, double mHeight)
{
	m_position = Vector2f(200, 200);
	m_rect = sf::RectangleShape(sf::Vector2f(50, 50));
	m_rect.setOrigin(25, 25);
	m_rect.setPosition(sf::Vector2f(m_position.x, m_position.y));

	if (!m_texture.loadFromFile("./Resources/Sprites/Spaceship_Player.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	m_rect.setTexture(&m_texture);
	rotation = 0;
	m_rect.setRotation(rotation);
	m_speed = 0;
	maxSpeed = 100;
	float x = cos(rotation * DEG_TO_RAD) * m_speed;
	float y = sin(rotation * DEG_TO_RAD) * m_speed;
	m_velocity = Vector2f(x, y);
	mapWidth = mWidth;
	mapHeight = mHeight;
}

Player::~Player()
{

}

void Player::update(double dt, Map& map, std::list<Projectile>& projectiles)
{


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		speedUp();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		speedDown();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		rotateLeft();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rotateRight();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (shotCooldown > maxCooldown)
		{
			projectiles.push_back(std::move(Projectile(m_position, 1, rotation, mapWidth, mapHeight)));
			shotCooldown = 0;
		}
	}
	shotCooldown++;


	//METHOD
	if (m_position.x < -(m_rect.getSize().x / 2))
	{
		m_position.x = mapWidth + (m_rect.getSize().x / 2);
	}
	else if (m_position.x - (m_rect.getSize().x / 2) > mapWidth)
	{
		m_position.x = -(m_rect.getSize().x / 2);
	}
	else if (m_position.y < -(m_rect.getSize().y / 2))
	{
		m_position.y = mapHeight + (m_rect.getSize().y / 2);
	}
	else if (m_position.y - (m_rect.getSize().y / 2) > mapHeight)
	{
		m_position.y = -(m_rect.getSize().y / 2);
	}
	//

	float x = cos(rotation * DEG_TO_RAD);
	float y = sin(rotation * DEG_TO_RAD);
	m_velocity = Vector2f(x, y);
	if (m_velocity.magnitude() > 0)
	{
		m_velocity = m_velocity.normalise();
	}
	m_velocity *= m_speed;
	m_position += m_velocity * (1 / 60.0f);
	m_rect.setPosition(sf::Vector2f(m_position.x, m_position.y));
	sf::FloatRect hitbox = sf::FloatRect(m_rect.getPosition().x - (m_rect.getSize().x / 2), m_rect.getPosition().y - (m_rect.getSize().y / 2), m_rect.getSize().x, m_rect.getSize().y);
	if (map.checkCollision(hitbox))
	{
		m_position -= m_velocity * (1 / 60.0f);
		m_rect.setPosition(sf::Vector2f(m_position.x, m_position.y));
	}
	m_rect.setRotation(rotation);
}

void Player::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
}

int Player::random(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, max);
	return dis(gen);
}

void Player::speedUp()
{
	if (m_speed <= maxSpeed)
	{
		m_speed += 2;
	}
}

void Player::speedDown()
{
	if (m_speed > 0)
	{
		m_speed -= 2;
	}
}

void Player::rotateRight()
{
	rotation++;
}

Vector2f Player::getPosition()
{
	return Vector2f(m_position);
}

Vector2f Player::getVelocity()
{
	return m_velocity;
}

void Player::rotateLeft()
{
	rotation--;
}