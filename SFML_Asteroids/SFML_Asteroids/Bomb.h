#pragma once
#include "GameObject.h"

class Bomb : public GameObject
{
public:
	Bomb(const sf::Vector2f& Position, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager);
	virtual void Update(sf::RenderWindow* Window, float DeltaTime);

	inline virtual void ApplyDrag(float DeltaTime) { /* Do Nothing */ };
	virtual void CollidedWith(GameObject* Other);
	inline virtual bool IsDetonated() { return m_Detonate; }

private:
	float m_TimeAlive;
	bool m_Detonate;
	float m_ExplosionTime;
};