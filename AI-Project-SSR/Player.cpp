#include "Player.h"
#include <random>
#include <iostream>

double const Player::DEG_TO_RAD = 0.0174533;

Player::Player()
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
}

Player::~Player()
{

}

void Player::update(double dt)
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


	//METHOD
	if (m_position.x < -50)
	{
		m_position.x = 1366 + 50;
	}
	else if (m_position.x - 50 > 1366)
	{
		m_position.x = -50;
	}
	else if (m_position.y < -50)
	{
		m_position.y = 768 + 50;
	}
	else if (m_position.y - 50 > 768)
	{
		m_position.y = -50;
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