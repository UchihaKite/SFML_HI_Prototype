#include "Asteroids.h"
#include "PlayState.h"
#include <random>
#include <ctime>
#include "SoundContainer.h"

std::mt19937 g_RandomGenerator(time(0));
std::uniform_int_distribution<int> g_RandomAngle(0, 360);
std::uniform_int_distribution<int> g_Random(1, 2);
std::uniform_int_distribution<int> g_RandomRPositive(45, 90);
std::uniform_int_distribution<int> g_RandomRNegative(-90, -45);

Asteroid::Asteroid(std::string TexturePath, const sf::Vector2f& Position)
	: GameObject(TexturePath, Position)
{
	int s_RandomAngle = g_RandomAngle(g_RandomGenerator);
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

	m_DestroySound = SoundContainer::GetSound("Game Assets/Audio/BlowUp.wav");
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

SmallAsteroid::SmallAsteroid(const sf::Vector2f& Position)
	: Asteroid("Game Assets/Sprites/PNG/Meteors/meteorBrown_small2.png", Position)
{
	m_CollisionRadius = 15;
	m_DestroySound = SoundContainer::GetSound("Game Assets/Audio/BlowUp.wav");
}

void SmallAsteroid::Destroy()
{
	m_DestroySound.play();
	Asteroid::Destroy();
}

MedAsteroid::MedAsteroid(const sf::Vector2f& Position)
	: Asteroid("Game Assets/Sprites/PNG/Meteors/meteorBrown_med1.png", Position)
{
	m_CollisionRadius = 30.0f;
	m_DestroySound = SoundContainer::GetSound("Game Assets/Audio/BlowUp.wav");
}

void MedAsteroid::Destroy()
{
	m_DestroySound.play();
	Asteroid::Destroy();

	// Create Small Asteroids upon being destroyed
	for (int i = 0; i < 2; i++)
	{
		SmallAsteroid* s_Small = new SmallAsteroid(m_Position);
		s_Small->SetAngle(g_RandomAngle(g_RandomGenerator));
		s_Small->SetVelocity(50);
		m_Owner->AddObject(s_Small);
	}
}

LargeAsteroid::LargeAsteroid(const sf::Vector2f& Position)
	: Asteroid("Game Assets/Sprites/PNG/Meteors/meteorBrown_big1.png", Position)
{
	// Collision Radius is set in the Parent Class
	m_DestroySound = SoundContainer::GetSound("Game Assets/Audio/BlowUp.wav");
}

void LargeAsteroid::Destroy()
{
	m_DestroySound.play();
	Asteroid::Destroy();
	m_DestroySound.play();
	// Create Medium Asteroids upon being destroyed
	for (int i = 0; i < 3; i++)
	{
		MedAsteroid* s_Medium = new MedAsteroid(m_Position);
		s_Medium->SetAngle(g_RandomAngle(g_RandomGenerator));
		s_Medium->SetVelocity(75);
		m_Owner->AddObject(s_Medium);
	}
}