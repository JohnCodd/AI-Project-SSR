#include "AI.h"
#include <random>

double const AI::DEG_TO_RAD = 0.0174533;
double const AI::RAD_TO_DEG = 57.2958;

AI::AI(double mWidth, double mHeight)
{
	m_position = Vector2f(400, 400);
	m_rect = sf::RectangleShape(sf::Vector2f(100, 100));
	m_rect.setOrigin(50, 50);
	m_rect.setPosition(sf::Vector2f(m_position.x, m_position.y));
	if (!m_texture.loadFromFile("./Resources/Sprites/Spaceship_Enemy.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	m_rect.setTexture(&m_texture);
	m_rect.setRotation(m_rotation);
	m_speed = 7;
	maxSpeed = 50;
	m_rotation = random(0, 360);

	float x = cos(m_rotation * DEG_TO_RAD) * m_speed;
	float y = sin(m_rotation * DEG_TO_RAD) * m_speed;
	m_velocity = Vector2f(x, y);
	moveState = "DEFAULT";
	mapWidth = mWidth;
	mapHeight = mHeight;
}

AI::AI(Vector2f position, std::string state, double mWidth, double mHeight)
{
	m_position = position;
	m_rect = sf::RectangleShape(sf::Vector2f(100, 100));
	m_rect.setOrigin(50, 50);
	m_rect.setPosition(sf::Vector2f(m_position.x, m_position.y));
	if (!m_texture.loadFromFile("./Resources/Sprites/Spaceship_Enemy.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	m_rect.setTexture(&m_texture);
	m_rect.setRotation(m_rotation);
	maxSpeed = 50;
	m_speed = maxSpeed;
	m_rotation = 0;
	moveState = state;
	m_velocity = Vector2f(0, 0);

	float x = cos(m_rotation * DEG_TO_RAD) * m_speed;
	float y = sin(m_rotation * DEG_TO_RAD) * m_speed;
	m_velocity = Vector2f(x, y);
	mapWidth = mWidth;
	mapHeight = mHeight;
}

AI::~AI()
{

}

void AI::update(float dt, Vector2f target, Tile& targetTile)
{
	target = Vector2f(targetTile.getEnd().x, targetTile.getEnd().y);
	if (moveState == "Seek")
	{
		seek(target);
	}
	else if (moveState == "Wander")
	{
		wander(target);
	}
	else if (moveState == "Arrive")
	{
		arrive(target);
	}
	m_position += m_velocity * (1 / 60.0f);
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
	m_rect.setPosition(sf::Vector2f(m_position.x, m_position.y));
	m_rect.setRotation(m_rotation);
}

void AI::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
}

int AI::random(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, max);
	return dis(gen);
}

void AI::seek(Vector2f player)
{
	float dt = (1 / 60.0f);
	auto desired = Vector2f(player - m_position).normalise() * m_speed;

	auto steering = desired - m_velocity;

	m_velocity += steering * dt;
	m_rotation = getOrientation(m_velocity);
}

void AI::wander(Vector2f player)
{
	/*
	sf::Vector2f diff = player - m_position;
	float test = mag(diff);
	diff = normalize(diff);
	/**/
	float angle = atan2(-m_velocity.x, m_velocity.y);
	//const float offsetX = (10.0f * DEG_TO_RAD) * (random(-100, 100) / 100.0f);
	//const float offsetY = (10.0f * DEG_TO_RAD) * (random(-100, 100) / 100.0f);
	angle = (angle + random(-1, 1));
	m_velocity = Vector2f(cos(angle), sin(angle)) * m_speed;
	m_rotation = angle * RAD_TO_DEG;
	//float angle = atan2(-(m_position.y - player.y), -(m_position.x - player.x));
	//const float offsetX = (10.0f * DEG_TO_RAD) * (random(-100, 100) / 100.0f);
	//const float offsetY = (10.0f * DEG_TO_RAD) * (random(-100, 100) / 100.0f);
	//m_velocity = sf::Vector2f(cos(angle) + offsetX, sin(angle) + offsetY) * m_speed;
	//m_rotation = angle * RAD_TO_DEG;
}

void AI::arrive(Vector2f player)
{
	m_speed = maxSpeed;

	if (player.distance(m_position) < 250)
	{
		m_speed *= 0.5f;
	}
	if (player.distance(m_position) < 100)
	{
		m_speed = 0;
	}

	seek(player);
}

float length(sf::Vector2f vector)
{
	return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}