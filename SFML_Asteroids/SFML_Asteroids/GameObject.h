#pragma once
#include "TextureHolder.h"
#include <string>

#define DEG_TO_RAD (0.0174532925f) // Degrees to Radians

class PlayState; // Forward declare the "GameState" Where all the Gameplay happens

class GameObject
{
public:
	GameObject(std::string TexturePath, const sf::Vector2f& Position);

	virtual void Update(sf::RenderWindow* Window, float DeltaTime);
	virtual void Draw(sf::RenderWindow* Window);

	virtual void LimitVelocity(float DeltaTime);
	virtual void ApplyDrag(float DeltaTime);
	virtual void WentOffEdgeOfScreen(bool OffScreen) {};

	virtual void CollidedWith(GameObject* Other) {};
	bool IsColliding(GameObject* Other);

	virtual void Destroy();
	bool IsDestroyed();

	void SetOwner(PlayState* Owner);

	void SetAngle(float Angle);
	float GetAngle();

	void SetPosition(const sf::Vector2f& Position);
	sf::Vector2f GetPosition() { return m_Position; }

	void SetAccel(float Amount);
	void SetVelocity(float Amount);

protected:
	sf::Vector2f m_Position;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Accel;

	sf::Sprite m_Sprite;
	sf::Texture m_Texture;

	PlayState* m_Owner;

	float m_Angle;
	float m_CollisionRadius;
	bool m_Destroyed;
};