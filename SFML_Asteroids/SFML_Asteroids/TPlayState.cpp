#include "TPlayState.h"
#include "StateMachine.h"
/*^ This is included to avoid the "pointer to incomplete class type"
error, as a result of forward declaring the StateMachine.*/
#include "Player.h"
#include "TextureManager.h"
#include "Asteroids.h"

#include <random>
#include <ctime>

#include <iostream>

#include <iomanip>

std::mt19937 g_TRandomGenerator2((unsigned int)time(0));
std::uniform_real_distribution<float> g_TRandomLocationX(0.0f, sf::VideoMode::getDesktopMode().width / 2.0f);
std::uniform_real_distribution<float> g_TRandomLocationY(0.0f, sf::VideoMode::getDesktopMode().height / 2.0f);
std::uniform_real_distribution<float> g_TRandomSpeed(100.0f, 300.0f);

TPlayState::TPlayState(StateMachine* Machine, Engine* Engine, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager, std::shared_ptr<int> NumPlayers) :
	PlayState(Machine, Engine, SoundManager, TextureManager),
	m_ScoreTracker(0),
	m_LevelTracker(1),
	m_ProceedLevel(false),
	m_TimeUntilRespawn(2.0f),
	m_RespawnTime(m_TimeUntilRespawn),
	m_IsGameOver(false),
	m_GameTimer(60.0f),
	m_MaxGameTime(m_GameTimer),
	m_NumPlayers(NumPlayers),
	m_CurrentPlayer(0)
{
	m_ScoreManager = std::make_unique<ScoreManager>("Game Assets/GameData/TournamentScore.txt");

	m_Font.loadFromFile("Game Assets/Font/kenpixel_high_square.ttf");

	SetUpText();
}

void TPlayState::Update(sf::RenderWindow* Window, float DeltaTime)
{
	m_ScoreManager->Update(m_ScoreTracker);

	if (m_GameTimer > 0.0f)
	{
		m_GameTimer -= DeltaTime;
		UpdateGameTime(m_GameTimer);
	}
	else
	{
		m_GameTimer = 0.0f;
		UpdateGameTime(m_GameTimer);
	}

	if (m_TimeUntilRespawn > 0.0f)
	{
		m_TimeUntilRespawn -= DeltaTime;
		if (m_TimeUntilRespawn <= 0.0f && m_GameTimer > m_RespawnTime)
		{
			Player* s_Player = new Player(PLAYER, sf::Vector2f(sf::VideoMode::getDesktopMode().width / 4.0f, sf::VideoMode::getDesktopMode().height / 4.0f), m_SoundManager, m_TextureManager);
			AddObject(s_Player);
		}
	}

	for (unsigned int i = 0; i < m_GameObjects.size(); i++)
	{
		GameObject* s_Current = m_GameObjects[i];
		s_Current->Update(Window, DeltaTime);
	}

	for (unsigned int i = 0; i < m_GameObjects.size(); i++)
	{
		GameObject* s_Current = m_GameObjects[i];
		for (unsigned int j = 0; j < m_GameObjects.size(); j++)
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
			if (dynamic_cast<Player*>(s_Current) != NULL && m_GameTimer < m_RespawnTime + 2.0f && m_CurrentPlayer < *m_NumPlayers)
			{
				m_Machine->ChangeState("RoundState");
			}
			if (dynamic_cast<Player*>(s_Current) != NULL && m_GameTimer < m_RespawnTime + 2.0f && m_CurrentPlayer == *m_NumPlayers)
			{
				m_Machine->ChangeState("GameOverState");
			}
			if (dynamic_cast<Player*>(s_Current) != NULL && m_GameTimer > m_RespawnTime)
			{
				m_TimeUntilRespawn = m_RespawnTime += 2.0f;
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
				m_LevelText.setString(std::string());
				m_ssLevelText << "Level: " << m_LevelTracker;
				m_LevelText.setString(m_ssLevelText.str());
				SpawnAsteroids(m_LevelTracker);
			}
		}
	}
}

void TPlayState::SetUpText()
{
	m_GameTimerText.setFont(m_Font);
	m_GameTimerText.setCharacterSize(30);
	m_GameTimerText.setFillColor(sf::Color::White);
	m_GameTimerText.setPosition(sf::VideoMode::getDesktopMode().width / 25.0f, sf::VideoMode::getDesktopMode().height / 80.0f);

	std::stringstream s_SStream;
	s_SStream << "Game Time: " << m_GameTimer;
	m_GameTimerText.setString(s_SStream.str());

	m_LevelText.setFont(m_Font);
	m_LevelText.setCharacterSize(30);
	m_LevelText.setFillColor(sf::Color::White);
	m_LevelText.setPosition(sf::VideoMode::getDesktopMode().width / 4.5f, sf::VideoMode::getDesktopMode().height / 30.0f);

	std::stringstream s_sstream;
	s_sstream << "Level: " << m_LevelTracker;
	m_LevelText.setString(s_sstream.str());
}


void TPlayState::UpdateGameTime(float GameTimer)
{
	if (m_GameTimer != m_MaxGameTime)
	{
		m_ssGameTimerText.str(std::string());
		m_ssGameTimerText << "Game Timer: " << std::fixed << std::setprecision(2) << m_GameTimer;
		m_GameTimerText.setString(m_ssGameTimerText.str());
	}
}

void TPlayState::Draw(sf::RenderWindow* Window)
{
	for (unsigned int i = 0; i < m_GameObjects.size(); i++)
	{
		GameObject* s_Current = m_GameObjects[i];
		s_Current->Draw(Window);
	}

	Window->draw(m_GameTimerText);
	Window->draw(m_LevelText);
	m_ScoreManager->Draw(Window);
}

void TPlayState::OnEnter()
{
	m_GameObjects.clear();
	SpawnAsteroids(m_LevelTracker);
	m_TimeUntilRespawn = 2.0f;
	m_RespawnTime = m_TimeUntilRespawn;
}

void TPlayState::OnExit()
{
	m_ScoreManager->StoreHighScore(m_ScoreTracker);
	m_ScoreTracker = 0;
	m_LevelTracker = 1;
	m_LevelText.setString(std::string());
	m_ssLevelText << "Level: " << m_LevelTracker;
	m_LevelText.setString(m_ssLevelText.str());
	m_ProceedLevel = false;
	m_IsGameOver = false;
	m_GameTimer = 60.0f;

	if (m_CurrentPlayer < *m_NumPlayers)
	{
		m_CurrentPlayer++;
	}
	else if (m_CurrentPlayer == *m_NumPlayers)
	{
		m_CurrentPlayer = 1;
		*m_NumPlayers = 0;
	}
}

void TPlayState::AddObject(GameObject* Object)
{
	// Also set the Objects "owner" variable
	Object->SetOwner(this);
	m_GameObjects.push_back(Object);
}

void TPlayState::UpdateScore(int Score)
{
	m_ScoreTracker += Score;
}

void TPlayState::SpawnAsteroids(int Level)
{
	if (Level == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			LargeAsteroid* s_NewAsteroid = new LargeAsteroid(sf::Vector2f(g_TRandomLocationX(g_TRandomGenerator2), g_TRandomLocationY(g_TRandomGenerator2)), m_SoundManager, m_TextureManager);
			s_NewAsteroid->SetVelocity(g_TRandomSpeed(g_TRandomGenerator2));
			AddObject(s_NewAsteroid);
		}
	}
	if (m_ProceedLevel == true)
	{
		for (int i = 0; i < 5 + Level; i++)
		{
			LargeAsteroid* s_NewAsteroid = new LargeAsteroid(sf::Vector2f(g_TRandomLocationX(g_TRandomGenerator2), g_TRandomLocationY(g_TRandomGenerator2)), m_SoundManager, m_TextureManager);
			s_NewAsteroid->SetVelocity(g_TRandomSpeed(g_TRandomGenerator2));
			AddObject(s_NewAsteroid);
		}
		m_ProceedLevel = false;
	}
}