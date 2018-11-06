#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f & pos)
	: GameObject("Sprites/PNG/Lasers/laserBlue08.png", pos)
	, m_TimeAlive(0.0f)
{
	m_Sprite.setScale(0.5, 0.5);
	m_CollisionRadius = 20.0f;
}

void Bullet::Update(sf::RenderWindow * window, float dt)
{
	if (m_TimeAlive > 3.0f)
	{
		Destroy();
	}

	GameObject::Update(window, dt);
	m_TimeAlive += dt;
}

void Bullet::CollideWith(GameObject* Other)
{
	/*
	Keeping this here to remind me of how I will structure the
	Asteroid Classes. It'll be similar to how I did
	"GameObject"s and the Derived Classes.
	Will finish 11/7/2018
	*/

	/*
	Asteroid* s_Asteroid = dynamic_cast<Asteroid*>(Other);
	if (s_Asteroid != nullptr)
	{
		if (dynamic_cast<LargeAsteroid*>(Other) != NULL)
		{
			m_Owner->UpdateScore(100);
		}
		else if (dynamic_cast<MedAsteroid*>(Other) != NULL)
		{
			m_Owner->UpdateScore(50);
		}
		else if (dynamic_cast<SmallAsteroid*>(Other) != NULL)
		{
			m_Owner->UpdateScore(25);
		}

		Destroy();
		Other->Destroy();
	}
	*/
}