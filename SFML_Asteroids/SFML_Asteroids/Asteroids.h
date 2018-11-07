#pragma once
#include "GameObject.h"

class Asteroid : public GameObject
{
public:
	Asteroid(std::string TexturePath, const sf::Vector2f& Position);
	virtual void Update(sf::RenderWindow* Window, float DeltaTime);
	virtual void ApplyDrag(float DeltaTime) { /* Do Nothing */ }
private:
	bool m_Rotation;
};

/*
Each Asteroid gets destroyed in a different way
They also will have different "m_CollisionRadius"
*/

class SmallAsteroid : public Asteroid
{
public:
	SmallAsteroid(const sf::Vector2f& Position);
	virtual void Destroy();
};

class MedAsteroid : public Asteroid
{
public:
	MedAsteroid(const sf::Vector2f& Position);
	virtual void Destroy();
};

class LargeAsteroid : public Asteroid
{
public:
	LargeAsteroid(const sf::Vector2f& Position);
	virtual void Destroy();
};