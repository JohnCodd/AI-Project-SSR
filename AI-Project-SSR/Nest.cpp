#include "Nest.h"

Nest::Nest(Vector2f position, double mapX, double mapY) : AI(position, "Stay", mapX, mapY)
{
	m_rect = sf::RectangleShape(sf::Vector2f(100, 100));
	m_rect.setOrigin(50, 50);
	m_rect.setPosition(sf::Vector2f(m_position.x, m_position.y));
	auto texture = sf::Texture();
	if (!texture.loadFromFile("./Resources/Sprites/Space_Station.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	else
	{
		m_texture = std::make_shared<sf::Texture>(std::move(texture));
	}
	m_rect.setTexture(m_texture.get(), true);
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
	health = maxHealth;
}

void Nest::update(float dt, Player& player, Tile & targetTile, Map& map, std::list<AI>& predators)
{
	Vector2f target = player.getPosition();
	if (active)
	{
		m_position = Vector2f(targetTile.getCenter().x, targetTile.getCenter().y);
		m_rect.setPosition(targetTile.getCenter());
		scanArea.setPosition(targetTile.getCenter());
		if (target.distance(m_position) < firingRadius && missiles.size() < misileLimit && shotCooldown > maxShotCooldown)
		{
			shotCooldown = 0;
			Missile m = std::move(Missile(m_position, 0.1f, m_rotation, mapWidth, mapHeight));
			missiles.push_back(m);
		}
	}
	for (auto& m : missiles)
	{
		m.update(dt, target, map);
		if (player.getRect().getGlobalBounds().intersects(sf::FloatRect(m.getPosition().x, m.getPosition().y, 2, 2)))
		{
			m.setActive(false);
			player.damage(3);
		}
	}
	missiles.erase(std::remove_if(missiles.begin(), missiles.end(), removeUnactiveProjectiles()),
		missiles.end());
	if (missiles.size() == 0)
	{
		shotCooldown++;
	}
	if (spawnCooldown > maxSpawnCooldown && spawnCount < maxSpawns)
	{
		spawnCooldown = 0;
		spawnCount++;
		AI a = AI(m_position, "Seek", mapWidth, mapHeight);
		predators.push_back(a);
	}
	spawnCooldown++;
}

void Nest::render(sf::RenderWindow& window)
{
	if (active)
	{
		window.draw(m_rect);
		window.draw(scanArea);
	}
	for (auto& m : missiles)
	{
		m.render(window);
	}
}

void Nest::damage()
{
	health--;
	if (health <= 0)
	{
		active = false;
	}
}
