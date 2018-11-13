#include "Bullet.h"
#include "Asteroids.h"
#include "PlayState.h"

Bullet::Bullet(const sf::Vector2f & Position)
	: GameObject("Game Assets/Sprites/PNG/Lasers/laserBlue08.png", Position)
	, m_TimeAlive(0.0f)
{
	m_Sprite.setScale(0.5, 0.5);
	m_CollisionRadius = 20.0f;
}

void Bullet::Update(sf::RenderWindow* Window, float DeltaTime)
{
	if (m_TimeAlive > 3.0f)
	{
		Destroy();
	}

	GameObject::Update(Window, DeltaTime);
	m_TimeAlive += DeltaTime;
}

void Bullet::CollidedWith(GameObject* Other)
{
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
}