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
	Vector2f getPosition();
	Vector2f getVelocity();
	int random(int min, int max);
	double static const DEG_TO_RAD;
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
};