#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(std::string TexturePath, const sf::Vector2f& Position);
	virtual void Draw(sf::RenderWindow* Window);
	virtual void Update(sf::RenderWindow* Window, float DeltaTime);
	virtual void CollidedWith(GameObject* Other);

	sf::Vector2f CurrentPosition();
	float GetRotation();

	bool IsFiring();
	bool IsInvulnerable();
	void SetInvulernable();
private:
	bool m_Firing;
	float m_Cooldown;
	float m_Timer;
	bool m_IsInvulnerable;

	sf::Sound m_ShootingSound;
	sf::Sound m_DyingSound;
	sf::Sound m_RespawnSound;
};