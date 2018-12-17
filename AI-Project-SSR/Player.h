#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2f.h"

class Player
{
public:
	Player();
	~Player();
	void update(double dt);
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
};