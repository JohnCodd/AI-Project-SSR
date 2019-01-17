#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2f.h"
#include "Map.h"
#include "Projectile.h"
#include <list>

class Player
{
public:
	Player(double mWidth, double mHeight);
	~Player();
	void update(double dt, Map& map, std::list<Projectile>& projectiles);
	void render(sf::RenderWindow & window);
	void speedUp();
	void speedDown();
	void rotateLeft();
	void rotateRight();
	void damage(int damage);
	Vector2f getPosition();
	Vector2f getVelocity();
	int random(int min, int max);
	int getHealth() { return health; }
	int getMaxHealth() { return maxHealth; }
	double static const DEG_TO_RAD;
	sf::RectangleShape getRect();
private:
	Vector2f m_position;
	Vector2f m_velocity;
	sf::RectangleShape m_rect;
	sf::Texture m_texture;
	float rotation;
	float m_speed;
	float maxSpeed;
	double mapWidth;
	double mapHeight;
	int shotCooldown, health;
	int maxHealth = 10;
	int maxCooldown = 100;
};