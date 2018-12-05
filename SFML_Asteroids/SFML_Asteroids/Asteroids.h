#pragma once
#include "GameObject.h"

class Asteroid : public GameObject
{
public:
	Asteroid(TextureType Type, const sf::Vector2f& Position, SoundManager* SoundManager, TextureManager* TextureManager);
	virtual void Update(sf::RenderWindow* Window, float DeltaTime);
	inline virtual void ApplyDrag(float DeltaTime) { /* Do Nothing */ }
protected:
	bool m_Rotation;
};

/*
Each Asteroid gets destroyed in a different way
They also will have different "m_CollisionRadius"
*/

class SmallAsteroid : public Asteroid
{
public:
	SmallAsteroid(const sf::Vector2f& Position, SoundManager* SoundManager, TextureManager* TextureManager);
	virtual void Destroy();
};

class MedAsteroid : public Asteroid
{
public:
	MedAsteroid(const sf::Vector2f& Position, SoundManager* SoundManager, TextureManager* TextureManager);
	virtual void Destroy();
};

class LargeAsteroid : public Asteroid
{
public:
	LargeAsteroid(const sf::Vector2f& Position, SoundManager* SoundManager, TextureManager* TextureManager);
	virtual void Destroy();
};