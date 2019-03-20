#include "Power-Ups.h"
#include "PlayState.h"
#include <random>
#include <ctime>
#include "Player.h"
#include "Bullet.h"
#include "TextureManager.h"

std::mt19937 g_RandomGenerator3((unsigned int)time(0));
std::uniform_real_distribution<float> g_RAngle(0, 360);
std::uniform_real_distribution<float> g_R(1, 2);
std::uniform_real_distribution<float> g_RPositive(45, 90);
std::uniform_real_distribution<float> g_RNegative(-90, -45);

PowerUps::PowerUps(TextureType Type, const sf::Vector2f& Position, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager)
	:
	GameObject(Type, Position, SoundManager, TextureManager),
	m_LifeTime(10.0f),
	m_Obtained(false),
	m_Type(Type)
{
	float s_RandomAngle = g_RAngle(g_RandomGenerator3);
	m_CollisionRadius = 50.0f;
	SetAngle(s_RandomAngle);

	// Determines how the power-ups Rotate
	if (g_R(g_RandomGenerator3) < 2)
	{
		m_Rotation = true;
	}
	else
	{
		m_Rotation = false;
	}
}

void PowerUps::Draw(sf::RenderWindow* Window)
{
	GameObject::Draw(Window);
}

void PowerUps::Update(sf::RenderWindow* Window, float DeltaTime)
{
	GameObject::Update(Window, DeltaTime);

	Duration(DeltaTime);

	// Just to add some randomization to how the power-ups rotate
	if (m_Rotation)
	{
		SetAngle(GetAngle() + g_RPositive(g_RandomGenerator3) * DeltaTime);
	}
	else
	{
		SetAngle(GetAngle() + g_RNegative(g_RandomGenerator3) * DeltaTime);
	}
}

void PowerUps::CollidedWith(GameObject* Other)
{
	Player* s_Player = dynamic_cast<Player*>(Other);
	Bullet* s_Bullet = dynamic_cast<Bullet*>(Other);
	if (s_Player != nullptr || s_Bullet != nullptr)
	{
		Obtained();
		Destroy();
		m_SoundManager->PlaySound(GAMEOBJECT_EXPLOSION);
	}
}

void PowerUps::Obtained()
{
	m_Obtained = true;
}

bool PowerUps::GetObtained()
{
	return m_Obtained;
}

PowerUpType PowerUps::GetPowerUp()
{
	switch (m_Type)
	{
	case 5: return PowerUpType::BONUSPOINTS;
		break;

	case 6: return PowerUpType::ICECREAM;
		break;

	case 7: return PowerUpType::PLAYTIME;
		break;

	case 8: return PowerUpType::THEBOMB;
		break;

	case 9: return PowerUpType::THESHIELD;
		break;

	default: break;
	}
}

void PowerUps::Duration(float DeltaTime)
{
	m_LifeTime -= DeltaTime;

	if (m_LifeTime <= 0.0f)
	{
		Destroy();
	}
}