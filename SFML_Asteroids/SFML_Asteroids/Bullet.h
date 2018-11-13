#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(const sf::Vector2f& Position);
	virtual void Update(sf::RenderWindow* Window, float DeltaTime);
	
	virtual void ApplyDrag(float DeltaTime) { /* Do Nothing */ };
	virtual void CollidedWith(GameObject* Other);

private:
	float m_TimeAlive;
};