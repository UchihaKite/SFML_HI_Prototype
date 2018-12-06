#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(const sf::Vector2f& Position, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager);
	virtual void Update(sf::RenderWindow* Window, float DeltaTime);
	
	virtual void ApplyDrag(float DeltaTime) { /* Do Nothing */ };
	virtual void CollidedWith(GameObject* Other);

private:
	float m_TimeAlive;
};