#include "Bomb.h"
#include "Asteroids.h"
#include "PlayState.h"
#include "TextureManager.h"

Bomb::Bomb(const sf::Vector2f & Position, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager)
	: GameObject(BOMB, Position, SoundManager, TextureManager)
	, m_TimeAlive(0.0f)
	, m_Detonate(false)
	, m_ExplosionTime(0.0f)
{
	m_Sprite.setScale(0.5, 0.5);
	m_CollisionRadius = 0.0f;
}

void Bomb::Update(sf::RenderWindow* Window, float DeltaTime)
{
	if (m_TimeAlive > 2.0f)
	{
		SetVelocity(0);
		m_Detonate = true;
	}

	GameObject::Update(Window, DeltaTime);
	m_TimeAlive += DeltaTime;

	if (m_Detonate == true)
	{
		m_ExplosionTime += DeltaTime;
		m_CollisionRadius = 100.0f;
	}

	if (m_ExplosionTime >= 1.0f)
	{
		Destroy();
	}
}

void Bomb::CollidedWith(GameObject* Other)
{
	if (m_CollisionRadius == 100.0f)
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
			Other->Destroy();
		}
	}
}