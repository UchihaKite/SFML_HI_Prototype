#include "PlayState.h"
#include "StateMachine.h"
#include "Player.h"
#include "TextureHolder.h"
#include "Asteroids.h"
/*^ This is included to avoid the "pointer to incomplete class type"
error, as a result of forward declaring the StateMachine.*/

#include <random>
#include <ctime>

#include <iostream>

std::mt19937 g_RandomGenerator2(time(0));
std::uniform_int_distribution<int> g_RandomLocationX(0, sf::VideoMode::getDesktopMode().width / 2.0f);
std::uniform_int_distribution<int> g_RandomLocationY(0, sf::VideoMode::getDesktopMode().height / 2.0f);
std::uniform_int_distribution<int> g_RandomSpeed(100, 300);

PlayState::PlayState(StateMachine* Machine, Engine* Engine) :
	GameState(Machine, Engine),
	m_ScoreTracker(0),
	m_LivesRemaining(4),
	m_LevelTracker(1),
	m_ProceedLevel(false),
	m_TimeUntilRespawn(2.0f),
	m_IsGameOver(false)

{
	m_ScoreManager = new ScoreManager();

	m_Font.loadFromFile("Game Assets/Font/kenpixel_high_square.ttf");

	m_LivesTexture = TextureHolder::GetTexture("Game Assets/Sprites/PNG/playerShip2_red.png");
	m_LivesColor = sf::Color::White;
	m_LivesColor.a = 120;
}

void PlayState::Update(sf::RenderWindow* Window, float DeltaTime)
{
	m_ScoreManager->Update(m_ScoreTracker);

	if (m_TimeUntilRespawn > 0.0f)
	{
		m_TimeUntilRespawn -= DeltaTime;
		if (m_TimeUntilRespawn <= 0.0f)
		{
			Player* s_Player = new Player("Game Assets/Sprites/PNG/playerShip2_red.png", sf::Vector2f(sf::VideoMode::getDesktopMode().width / 4.0f, sf::VideoMode::getDesktopMode().height / 4.0f));
			AddObject(s_Player);
		}
	}

	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		GameObject* s_Current = m_GameObjects[i];
		s_Current->Update(Window, DeltaTime);
	}

	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		GameObject* s_Current = m_GameObjects[i];
		for (int j = 0; j < m_GameObjects.size(); j++)
		{
			GameObject* s_Other = m_GameObjects[j];
			if (s_Current->IsColliding(s_Other))
			{
				s_Current->CollidedWith(s_Other);
			}
		}
	}

	for (int i = m_GameObjects.size() - 1; i >= 0; i--)
	{
		GameObject* s_Current = m_GameObjects[i];
		if (s_Current->IsDestroyed())
		{
			if (dynamic_cast<Player*>(s_Current) != NULL && m_LivesRemaining == 0)
			{
				m_Machine->ChangeState("GameOverState");
			}
			if (dynamic_cast<Player*>(s_Current) != NULL && m_LivesRemaining > 0)
			{
				m_TimeUntilRespawn = 2.0f;
				m_LivesRemaining--;
			}
			delete s_Current;
			m_GameObjects.erase(m_GameObjects.begin() + i);
		}
	}

	if (m_ProceedLevel == false)
	{
		for (int i = m_GameObjects.size() - 1; i >= 0; i--)
		{
			GameObject* s_Current = m_GameObjects[i];
			if (dynamic_cast<Player*>(s_Current) != NULL && m_GameObjects.size() == 1)
			{
				dynamic_cast<Player*>(s_Current)->SetInvulernable();
				m_ProceedLevel = true;
				m_LevelTracker += 1;
				SpawnAsteroids(m_LevelTracker);
			}
		}
	}
}

void PlayState::Draw(sf::RenderWindow* Window)
{
	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		GameObject* s_Current = m_GameObjects[i];
		s_Current->Draw(Window);
	}

	for (int i = 0; i < m_LivesRemaining; i++)
	{
		sf::Sprite s_PlayerLives;
		s_PlayerLives.setTexture(m_LivesTexture);
		s_PlayerLives.setScale(0.5f, 0.5f);
		s_PlayerLives.setColor(m_LivesColor);

		s_PlayerLives.setPosition((sf::VideoMode::getDesktopMode().width / 25.0f) + 50 * i, sf::VideoMode::getDesktopMode().height / 15.0f);
		Window->draw(s_PlayerLives);
	}
	m_ScoreManager->Draw(Window);
}

void PlayState::OnEnter()
{
	m_GameObjects.clear();
	SpawnAsteroids(m_LevelTracker);
}

void PlayState::OnExit()
{
	m_ScoreManager->StoreHighScore(m_ScoreTracker);
	m_ScoreTracker = 0;
	m_LevelTracker = 0;
	m_LivesRemaining = 4;
	m_ProceedLevel = false;
	m_TimeUntilRespawn = 2.0f;
	m_IsGameOver = false;
}

void PlayState::AddObject(GameObject* Object)
{
	// Also set thhe Objects "owner" variable
	Object->SetOwner(this);
	m_GameObjects.push_back(Object);
}

void PlayState::UpdateScore(int Score)
{
	m_ScoreTracker += Score;
}

void PlayState::SpawnAsteroids(int Level)
{
	if (Level == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			LargeAsteroid* s_NewAsteroid = new LargeAsteroid(sf::Vector2f(g_RandomLocationX(g_RandomGenerator2), g_RandomLocationY(g_RandomGenerator2)));
			s_NewAsteroid->SetVelocity(g_RandomSpeed(g_RandomGenerator2));
			AddObject(s_NewAsteroid);
		}
	}
	if (m_ProceedLevel == true)
	{
		for (int i = 0; i < 5 + Level; i++)
		{
			LargeAsteroid* s_NewAsteroid = new LargeAsteroid(sf::Vector2f(g_RandomLocationX(g_RandomGenerator2), g_RandomLocationY(g_RandomGenerator2)));
			s_NewAsteroid->SetVelocity(g_RandomSpeed(g_RandomGenerator2));
			AddObject(s_NewAsteroid);
		}
		m_ProceedLevel = false;
	}
}