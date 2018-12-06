#include "Asteroids.h"
#include "PlayState.h"
#include <random>
#include <ctime>
#include "TextureManager.h"

std::mt19937 g_RandomGenerator((unsigned int)time(0));
std::uniform_real_distribution<float> g_RandomAngle(0, 360);
std::uniform_real_distribution<float> g_Random(1, 2);
std::uniform_real_distribution<float> g_RandomRPositive(45, 90);
std::uniform_real_distribution<float> g_RandomRNegative(-90, -45);

Asteroid::Asteroid(TextureType Type, const sf::Vector2f& Position, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager)
	: GameObject(Type, Position, SoundManager, TextureManager)
{
	float s_RandomAngle = g_RandomAngle(g_RandomGenerator);
	m_CollisionRadius = 50.0f;
	SetAngle(s_RandomAngle);

	// Determines how the Asteroids Rotate
	if (g_Random(g_RandomGenerator) < 2)
	{
		m_Rotation = true;
	}
	else
	{
		m_Rotation = false;
	}
}

void Asteroid::Update(sf::RenderWindow* Window, float DeltaTime)
{
	GameObject::Update(Window, DeltaTime);

	// Just to add some randomization to how the asteroids rotate
	if (m_Rotation)
	{
		SetAngle(GetAngle() + g_RandomRPositive(g_RandomGenerator) * DeltaTime);
	}
	else
	{
		SetAngle(GetAngle() + g_RandomRNegative(g_RandomGenerator) * DeltaTime);
	}
}

SmallAsteroid::SmallAsteroid(const sf::Vector2f& Position, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager)
	: Asteroid(ASTEROID_SMALL, Position, SoundManager, TextureManager)
{
	m_CollisionRadius = 15;
}

void SmallAsteroid::Destroy()
{
	m_SoundManager->PlaySound(GAMEOBJECT_EXPLOSION);
	Asteroid::Destroy();
}

MedAsteroid::MedAsteroid(const sf::Vector2f& Position, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager)
	: Asteroid(ASTEROID_MED, Position, SoundManager, TextureManager)
{
	m_CollisionRadius = 30.0f;
}

void MedAsteroid::Destroy()
{
	m_SoundManager->PlaySound(GAMEOBJECT_EXPLOSION);
	Asteroid::Destroy();

	// Create Small Asteroids upon being destroyed
	for (int i = 0; i < 2; i++)
	{
		SmallAsteroid* s_Small = new SmallAsteroid(m_Position, m_SoundManager, m_TextureManager);
		s_Small->SetAngle(g_RandomAngle(g_RandomGenerator));
		s_Small->SetVelocity(50);
		m_Owner->AddObject(s_Small);
	}
}

LargeAsteroid::LargeAsteroid(const sf::Vector2f& Position, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager)
	: Asteroid(ASTEROID_LARGE, Position, SoundManager, TextureManager)
{
	// Collision Radius is set in the Parent Class
}

void LargeAsteroid::Destroy()
{
	m_SoundManager->PlaySound(GAMEOBJECT_EXPLOSION);
	Asteroid::Destroy();

	// Create Medium Asteroids upon being destroyed
	for (int i = 0; i < 3; i++)
	{
		MedAsteroid* s_Medium = new MedAsteroid(m_Position, m_SoundManager, m_TextureManager);
		s_Medium->SetAngle(g_RandomAngle(g_RandomGenerator));
		s_Medium->SetVelocity(75);
		m_Owner->AddObject(s_Medium);
	}
}