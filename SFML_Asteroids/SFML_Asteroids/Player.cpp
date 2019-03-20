#include "Player.h"
#include "PlayState.h"
#include "Asteroids.h"
#include "Bullet.h"
#include "ParticleSystem.h"
#include "TextureManager.h"
#include "Bomb.h"

Player::Player(TextureType Type, const sf::Vector2f& Position, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager)
	: GameObject(Type, Position, SoundManager, TextureManager),
	m_Firing(false),
	m_Cooldown(0.0f),
	m_Timer(0.0f),
	m_IsInvulnerable(true),
	m_BombObtained(false),
	m_BombCounter(0),
	m_ShieldObtained(false)

{
	m_SoundManager->PlaySound(PLAYER_RESPAWN);
}

void Player::Draw(sf::RenderWindow* Window)
{
	GameObject::Draw(Window);

	if (m_Timer < 3.0f)
	{
		sf::CircleShape s_Shape;
		s_Shape.setRadius(60);
		s_Shape.setFillColor(sf::Color::Transparent);
		s_Shape.setOutlineThickness(5 * m_Timer / 3.0f + 1);
		sf::Color s_Color = sf::Color::Blue;
		s_Color.a = (int)(255.0f * m_Timer / 3.0f);
		s_Shape.setOutlineColor(s_Color);
		s_Shape.setOrigin(60, 55);
		s_Shape.setPosition(m_Position.x, m_Position.y);
		Window->draw(s_Shape);
	}

	if (m_Timer < 3.0f)
	{
		float s_SinValue = sin(m_Timer * 25); // Between -1-1
		s_SinValue += 1.25; // Between 0-2
		s_SinValue *= 0.25; // Between 0-1	
		float s_Alpha = s_SinValue * 255.0f; // Between 0-255
		sf::Color s_ShipColor = sf::Color::White;
		s_ShipColor.a = (int)(s_Alpha);
		m_Sprite.setColor(s_ShipColor);
	}
	else
	{
		m_Sprite.setColor(sf::Color::White);
	}
}

void Player::Update(sf::RenderWindow* Window, float DeltaTime)
{
	if (m_ShieldObtained == true)
	{
		m_Timer = 0.0f;
		m_ShieldObtained = false;
	}
	m_Cooldown -= DeltaTime;
	m_Timer += DeltaTime;

	GameObject::Update(Window, DeltaTime);
	

	if (m_Timer >= 3.0f)
	{
		m_IsInvulnerable = false;
	}
	else
	{
		m_IsInvulnerable = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		SetAngle(GetAngle() + 180 * DeltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		SetAngle(GetAngle() - 180 * DeltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		SetAccel(400.0f);
		m_Owner->AddObject(new ParticleSystem(1, m_Position + sf::Vector2f(sin(DEG_TO_RAD * (m_Angle + 90)) * 50, -cos(DEG_TO_RAD * (m_Angle + 90)) * 50), sf::Color::Blue, 1, 0, -m_Angle, 400, 0, m_SoundManager, m_TextureManager));
		m_Owner->AddObject(new ParticleSystem(1, m_Position + sf::Vector2f(sin(DEG_TO_RAD * (m_Angle - 90)) * 50, -cos(DEG_TO_RAD * (m_Angle - 90)) * 50), sf::Color::Blue, 1, 0, -m_Angle, 400, 0, m_SoundManager, m_TextureManager));
	}
	else
	{
		SetAccel(0.0f);
	}

	if (m_Timer >= 3.0f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			m_Firing = true;
		}
		else
		{
			m_Firing = false;
		}
	}

	if (m_Firing && m_Cooldown <= 0.0f)
	{
		if (m_BombObtained == false)
		{
			// Wants to do a multishot here
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				m_Cooldown = 2.0f;
				m_SoundManager->PlaySound(PLAYER_SHOOTING);
				for (int i = 0; i < 3; i++)
				{
					Bullet* s_Bullet = new Bullet(m_Position, m_SoundManager, m_TextureManager);
					s_Bullet->SetAngle(m_Angle + i * 15 - 15);
					s_Bullet->SetVelocity(500);
					m_Owner->AddObject(s_Bullet);
				}
			}
			else
			{
				m_SoundManager->PlaySound(PLAYER_SHOOTING);
				m_Cooldown = 0.2f;
				Bullet* s_Bullet = new Bullet(m_Position, m_SoundManager, m_TextureManager);
				s_Bullet->SetAngle(m_Angle);
				s_Bullet->SetVelocity(500);
				m_Owner->AddObject(s_Bullet);
			}
		}
		else if (m_BombObtained == true && m_BombCounter < 3)
		{
			m_SoundManager->PlaySound(PLAYER_SHOOTING);
			m_Cooldown = 1.0f;
			Bomb* s_Bomb = new Bomb(m_Position, m_SoundManager, m_TextureManager);
			s_Bomb->SetAngle(m_Angle);
			s_Bomb->SetVelocity(300);
			m_Owner->AddObject(s_Bomb);
		}
		else if (m_BombObtained == true && m_BombCounter >= 3)
		{
			m_BombObtained = false;
			m_BombCounter = 0;
		}
	}
}

void Player::CollidedWith(GameObject* other)
{
	if (m_IsInvulnerable == false)
	{
		Asteroid* s_Asteroid = dynamic_cast<Asteroid*>(other);
		if (s_Asteroid != nullptr)
		{
			Destroy();
			m_SoundManager->PlaySound(PLAYER_DYING);
			m_IsInvulnerable = true;
		}
	}
}

sf::Vector2f Player::CurrentPosition()
{
	return m_Sprite.getPosition();
}
float Player::GetRotation()
{
	return m_Sprite.getRotation();
}

bool Player::IsFiring()
{
	return m_Firing;
}
bool Player::IsInvulnerable()
{
	return m_IsInvulnerable;
}

void Player::SetInvulernable()
{
	m_IsInvulnerable = true;
	m_Timer = 0.0f;
}