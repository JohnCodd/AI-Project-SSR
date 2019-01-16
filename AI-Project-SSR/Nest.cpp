#include "Nest.h"

Nest::Nest(Vector2f position, double mapX, double mapY) : AI(position, "Stay", mapX, mapY)
{
	m_rect = sf::RectangleShape(sf::Vector2f(100, 100));
	m_rect.setOrigin(50, 50);
	m_rect.setPosition(sf::Vector2f(m_position.x, m_position.y));
	if (!m_texture.loadFromFile("./Resources/Sprites/Space_Station.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	m_rect.setTexture(&m_texture);
	m_rect.setRotation(m_rotation);
	maxSpeed = 0;
	m_speed = maxSpeed;
	m_rotation = 0;
	m_velocity = Vector2f(0, 0);

	float x = cos(m_rotation * DEG_TO_RAD) * m_speed;
	float y = sin(m_rotation * DEG_TO_RAD) * m_speed;
	m_velocity = Vector2f(x, y);
	scanArea = sf::CircleShape(firingRadius);
	scanArea.setPosition(m_position.x, m_position.y);
	scanArea.setOrigin(sf::Vector2f(firingRadius, firingRadius));
	scanArea.setOutlineColor(sf::Color::Red);
	scanArea.setOutlineThickness(4);
	scanArea.setFillColor(sf::Color::Transparent);
}

void Nest::update(float dt, Vector2f target, Tile & targetTile)
{
	m_position = Vector2f(targetTile.getCenter().x, targetTile.getCenter().y);
	m_rect.setPosition(targetTile.getCenter());
	scanArea.setPosition(targetTile.getCenter());
	if (target.distance(m_position) < firingRadius && missiles.size() < misileLimit && shotCooldown > maxCooldown)
	{
		shotCooldown = 0;
		Missile m = std::move(Missile(m_position, 0.1f, m_rotation, mapWidth, mapHeight));
		missiles.push_back(m);
	}
	shotCooldown++;
	for (auto& m : missiles)
	{
		m.update(dt, target);
	}
	missiles.erase(std::remove_if(missiles.begin(), missiles.end(), removeUnactiveProjectiles()),
		missiles.end());
}

void Nest::render(sf::RenderWindow& window)
{
	window.draw(m_rect);
	window.draw(scanArea);
	for (auto& m : missiles)
	{
		m.render(window);
	}
}
