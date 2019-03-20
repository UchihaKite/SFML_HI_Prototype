#pragma once

#include "GameObject.h"

enum PowerUpType
{
	BONUSPOINTS = 5,
	ICECREAM,
	PLAYTIME,
	THEBOMB,
	THESHIELD,
	TOTAL = 5 //+1 for any Additional PowerUpTypes
};

class PowerUps : public GameObject
{
public:
	PowerUps(TextureType Type, const sf::Vector2f& Position, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager);
	virtual void Draw(sf::RenderWindow* Window);
	virtual void Update(sf::RenderWindow* Window, float DeltaTime);
	inline virtual void ApplyDrag(float DeltaTime) { /* Do Nothing */ }
	virtual void CollidedWith(GameObject* Other);

	void Obtained();
	bool GetObtained();
	PowerUpType GetPowerUp();
	void Duration(float DeltaTime);

private:
	float m_LifeTime;
	bool m_Obtained;
	bool m_Rotation;
	int m_Type;
};