#include <random>
#include <ctime>
#include "ParticleSystem.h"
#include "PlayState.h"

std::mt19937 g_MyGenerator(time(0));
std::uniform_int_distribution<int> g_RandomSize(1, 5);
std::uniform_int_distribution<int> g_RandomLifeTime(1, 5);

Particle::Particle(sf::Vector2f Position, sf::Color Color, float Size, float LifeTime, float InitialLifeTime, sf::Vector2f Velocity, sf::Vector2f Accel)
	: m_Position(Position),
	m_Color(Color),
	m_Size(Size),
	m_LifeTime(LifeTime),
	m_InitialLifeTime(InitialLifeTime),
	m_Velocity(Velocity),
	m_Accel(Accel)
{
}

ParticleSystem::ParticleSystem(float Count, sf::Vector2f Position, sf::Color Color, float Size, int Spread, float Angle, float Speed, int SpeedSpread)
	: GameObject("", Position)
{
	for (int i = 0; i < Count; i++)
	{
		float s_Size = Size + g_RandomSize(g_MyGenerator) / 2.0f;
		float s_LifeTime = 1.0f + g_RandomLifeTime(g_MyGenerator) / 10.0f;
		float s_InitialLifeTime = s_LifeTime;

		float s_RandomAngle = Angle + (Spread > 0.0f ? (rand() % Spread) : 0.0f);
		s_RandomAngle *= DEG_TO_RAD;

		float s_ParticleSpeed = Speed + (SpeedSpread > 0.0f ? (rand() % SpeedSpread) : 0.0f);
		sf::Vector2f s_Velocity = sf::Vector2f(sin(s_RandomAngle) * s_ParticleSpeed, cos(s_RandomAngle) * s_ParticleSpeed);
		sf::Vector2f s_Accel = sf::Vector2f(0.5f * -sin(s_RandomAngle) * s_ParticleSpeed, -0.5f * cos(s_RandomAngle) * s_ParticleSpeed);

		Particle s_NewParticle(Position, Color, s_Size, s_LifeTime, s_InitialLifeTime, s_Velocity, s_Accel);

		m_Particles.push_back(s_NewParticle);
	}
}

void ParticleSystem::Draw(sf::RenderWindow* Window)
{
	for (int i = 0; i < m_Particles.size(); i++)
	{
		Particle& s_Particle = m_Particles[i];

		m_Shape.setPosition(s_Particle.GetPosition());
		m_Shape.setFillColor(s_Particle.GetColor());
		m_Shape.setRadius(s_Particle.GetSize());
		m_Shape.setPointCount(6);
		Window->draw(m_Shape);
	}
}

void ParticleSystem::Update(sf::RenderWindow* Window, float DeltaTime)
{
	for (int i = 0; i < m_Particles.size(); i++)
	{
		Particle& s_Particle = m_Particles[i];
		s_Particle.SetVelocity(s_Particle.GetAccel() * DeltaTime);
		s_Particle.SetPosition(s_Particle.GetVelocity() * DeltaTime);
		s_Particle.SetLifeTime(DeltaTime);
		s_Particle.SetColor(255 * s_Particle.GetLifeTime() / s_Particle.GetInitialLifeTime());

		if (s_Particle.GetLifeTime() <= 0.0f)
		{
			m_Particles.erase(m_Particles.begin() + i);
			i--;
		}
	}

	if (m_Particles.size() <= 0)
	{
		Destroy();
	}
}