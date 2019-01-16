#pragma once
#include "Projectile.h"
class Missile :
	public Projectile
{
public:
	Missile(Vector2f position, float speed, float rotation, float mWidth, float mHeight);
	~Missile();
	void update(float dt, Vector2f target);
protected:
	float radius = 20;
private:
	sf::Texture texture;
};

