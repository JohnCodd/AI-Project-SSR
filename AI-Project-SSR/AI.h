#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vector2f.h"
#include "Tile.h"

class AI
{
public:
	AI(double mWidth, double mHeight);
	AI(Vector2f position, std::string state, double mWidth, double mHeight);
	~AI();
	void update(float dt, Vector2f target, Tile& targetTile);
	void render(sf::RenderWindow & window);
	void seek(Vector2f player);
	void wander(Vector2f player);
	void arrive(Vector2f player);
	void pursue(Vector2f player);
	virtual int random(int min, int max);
	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
	static float length(sf::Vector2f& v) { return sqrtf(v.x * v.x + v.y * v.y); }
	static float distance(sf::Vector2f v1, sf::Vector2f v2) { return sqrtf(powf((v2.x - v1.x), 2) + powf((v2.y - v1.y), 2)); }
	virtual Vector2f getPosition() { return m_position; }
	virtual float getOrientation(Vector2f vel) { return vel.magnitude() > 0 ? atan2(vel.y, vel.x) * RAD_TO_DEG : m_rotation; }
	virtual sf::Vector2f normalize(sf::Vector2f vector) {
		float m = length(vector);
		sf::Vector2f returnv = vector;
		if (m > 0)
		{
			returnv = vector / m;
		}
		return returnv;
	}

protected:
	Vector2f m_position;
	Vector2f m_velocity;
	sf::RectangleShape m_rect;
	sf::Texture m_texture;
	float m_rotation;
	float m_speed;
	float maxSpeed;
	std::string moveState;
	double mapWidth;
	double mapHeight;

};