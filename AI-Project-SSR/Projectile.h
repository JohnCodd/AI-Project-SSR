#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vector2f.h"
class Projectile
{
public:
	Projectile(Vector2f position, float speed, float rotation, float mWidth, float mHeight);
	~Projectile();
	void update(float dt);
	virtual void render(sf::RenderWindow& window);
protected:
	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
	Vector2f m_position, velocity;
	float m_rotation, mapWidth, mapHeight;
	float radius = 5;
	float m_speed;
	virtual float getOrientation(Vector2f vel) { return vel.magnitude() > 0 ? atan2(vel.y, vel.x) * RAD_TO_DEG : m_rotation; }
	sf::CircleShape collider;
	sf::RectangleShape rect;
	std::shared_ptr<sf::Texture> m_texture;
};

