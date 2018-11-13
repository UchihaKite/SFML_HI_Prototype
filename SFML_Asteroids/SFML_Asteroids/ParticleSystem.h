#pragma once
#include "GameObject.h"

class Particle
{
public:
	Particle(sf::Vector2f Position, sf::Color Color, float Size, float LifeTime, float InitialLifeTime, sf::Vector2f Velocity, sf::Vector2f Accel);
	inline sf::Vector2f GetPosition() { return m_Position; }
	inline sf::Vector2f GetVelocity() { return m_Velocity; }
	inline sf::Vector2f GetAccel() { return m_Accel; }
	inline sf::Color GetColor() { return m_Color; }

	inline float GetSize() { return m_Size; }
	inline float GetLifeTime() { return m_LifeTime; }
	inline float GetInitialLifeTime() { return m_InitialLifeTime; }

	inline void SetVelocity(sf::Vector2f Velocity) { m_Velocity += Velocity; }
	inline void SetPosition(sf::Vector2f Position) { m_Position += Position; }
	inline void SetLifeTime(float LifeTime) { m_LifeTime -= LifeTime; }
	inline void SetColor(int Color) { m_Color.a = Color; }
private:
	sf::Vector2f m_Position;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Accel;
	sf::Color m_Color;

	float m_Size;
	float m_LifeTime;
	float m_InitialLifeTime;
};

class ParticleSystem : public GameObject
{
public:
	ParticleSystem(float Count, sf::Vector2f Position, sf::Color Color, float Size, int Spread, float Angle, float Speed, int SpeedSpread);
	virtual void Draw(sf::RenderWindow* Window);
	virtual void Update(sf::RenderWindow* Window, float DeltaTime);
private:
	std::vector<Particle> m_Particles;
	sf::CircleShape m_Shape;
};