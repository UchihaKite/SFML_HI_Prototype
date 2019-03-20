#include "PlayState.h"
#include "StateMachine.h"
/*^ This is included to avoid the "pointer to incomplete class type"
error, as a result of forward declaring the StateMachine.*/
#include "Player.h"
#include "TextureManager.h"
#include "Asteroids.h"
#include "Power-Ups.h"

#include <random>
#include <ctime>

#include <iostream>

#include <iomanip>

//For Asteroids
std::mt19937 g_RandomGenerator2((unsigned int)time(0));
std::uniform_real_distribution<float> g_RandomLocationX(0.0f, sf::VideoMode::getDesktopMode().width / 2.0f);
std::uniform_real_distribution<float> g_RandomLocationY(0.0f, sf::VideoMode::getDesktopMode().height / 2.0f);
std::uniform_real_distribution<float> g_RandomSpeed(100.0f, 300.0f);

//For Power-Ups
std::mt19937 g_RandomGenerator4((unsigned int)time(0));
std::uniform_real_distribution<float> g_LocationX(0.0f, sf::VideoMode::getDesktopMode().width / 2.0f);
std::uniform_real_distribution<float> g_LocationY(0.0f, sf::VideoMode::getDesktopMode().height / 2.0f);
std::uniform_real_distribution<float> g_Speed(100.0f, 300.0f);
std::uniform_int_distribution<int> g_Type(5, 9);

PlayState::PlayState(StateMachine* Machine, Engine* Engine, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager) :
	GameState(Machine, Engine, SoundManager, TextureManager),
	m_ScoreTracker(0),
	m_LevelTracker(1),
	m_ProceedLevel(false),
	m_TimeUntilRespawn(2.0f),
	m_RespawnTime(m_TimeUntilRespawn),
	m_IsGameOver(false),
	m_GameTimer(60.0f),
	m_MaxGameTime(m_GameTimer),
	m_PowerUpTimer(10.0f),
	m_PowerUpSpawned(false),
	m_PowerUpAttack(false)
{
	m_Leaderboard = std::make_unique<Leaderboard>("Game Assets/GameData/LeaderboardScores.txt");

	m_Font.loadFromFile("Game Assets/Font/kenpixel_high_square.ttf");

	SetUpText();
}

void PlayState::Update(sf::RenderWindow* Window, float DeltaTime)
{
	m_Leaderboard->Update(m_ScoreTracker);

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

	if (m_GameTimer > 0.0f)
	{
		m_PowerUpTimer -= DeltaTime;

		if (m_PowerUpTimer <= 0.0f)
		{
			if (m_PowerUpSpawned == false && m_GameTimer > m_RespawnTime)
			{
				//int s_Type = g_Type(g_RandomGenerator4);
				int s_Type = 9;
				PowerUps* s_NewPowerUp;

				switch (s_Type)
				{
				case 5: s_NewPowerUp = new PowerUps(TextureType::BONUS_POINTS, sf::Vector2f(g_LocationX(g_RandomGenerator2), g_LocationY(g_RandomGenerator2)), m_SoundManager, m_TextureManager);
					s_NewPowerUp->SetVelocity(g_Speed(g_RandomGenerator2));
					AddObject(s_NewPowerUp);
					break;
				case 6: s_NewPowerUp = new PowerUps(TextureType::ICE_CREAM, sf::Vector2f(g_LocationX(g_RandomGenerator2), g_LocationY(g_RandomGenerator2)), m_SoundManager, m_TextureManager);
					s_NewPowerUp->SetVelocity(g_Speed(g_RandomGenerator2));
					AddObject(s_NewPowerUp);
					break;
				case 7: s_NewPowerUp = new PowerUps(TextureType::PLAY_TIME, sf::Vector2f(g_LocationX(g_RandomGenerator2), g_LocationY(g_RandomGenerator2)), m_SoundManager, m_TextureManager);
					s_NewPowerUp->SetVelocity(g_Speed(g_RandomGenerator2));
					AddObject(s_NewPowerUp);
					break;
				case 8: s_NewPowerUp = new PowerUps(TextureType::THE_BOMB, sf::Vector2f(g_LocationX(g_RandomGenerator2), g_LocationY(g_RandomGenerator2)), m_SoundManager, m_TextureManager);
					s_NewPowerUp->SetVelocity(g_Speed(g_RandomGenerator2));
					AddObject(s_NewPowerUp);
					break;
				case 9: s_NewPowerUp = new PowerUps(TextureType::THE_SHIELD, sf::Vector2f(g_LocationX(g_RandomGenerator2), g_LocationY(g_RandomGenerator2)), m_SoundManager, m_TextureManager);
					s_NewPowerUp->SetVelocity(g_Speed(g_RandomGenerator2));
					AddObject(s_NewPowerUp);
					break;
				}

				m_PowerUpSpawned = true;
			}
		}
	}

	for (int i = m_GameObjects.size() - 1; i >= 0; i--)
	{
		GameObject* s_Current = m_GameObjects[i];
		if (s_Current->IsDestroyed())
		{
			if (dynamic_cast<Player*>(s_Current) != NULL && m_GameTimer < m_RespawnTime + 2.0f)
			{
				m_Leaderboard->StoreHighScore(m_ScoreTracker);
				if (m_Leaderboard->GetInputNeeded() == false)
				{
					m_Machine->ChangeState("GameOverState");
				}
			}
			if (dynamic_cast<Player*>(s_Current) != NULL && m_GameTimer > m_RespawnTime)
			{
				m_TimeUntilRespawn = m_RespawnTime += 2.0f;
			}
			if (dynamic_cast<PowerUps*>(s_Current) != NULL && m_GameTimer > m_RespawnTime)
			{
				m_PowerUpTimer = 10.0f;
				m_PowerUpSpawned = false;
				if (dynamic_cast<PowerUps*>(s_Current)->GetObtained() == true)
				{
					switch (dynamic_cast<PowerUps*>(s_Current)->GetPowerUp())
					{
					case PowerUpType::BONUSPOINTS: m_ScoreTracker += 100;
						break;
					case PowerUpType::ICECREAM: m_GameTimer += 20.0f;
						m_PowerUpAttack = true;
						break;
					case PowerUpType::PLAYTIME: m_GameTimer += 10.0f;
						break;
					case PowerUpType::THEBOMB: 
						for (int i = m_GameObjects.size() - 1; i >= 0; i--)
						{
							GameObject* s_Current = m_GameObjects[i];
							if (dynamic_cast<Player*>(s_Current) != NULL)
							{
								dynamic_cast<Player*>(s_Current)->LoadBomb();
							}
						}
						break;
					case PowerUpType::THESHIELD: 
						for (int i = m_GameObjects.size() - 1; i >= 0; i--)
						{
							GameObject* s_Current = m_GameObjects[i];
							if (dynamic_cast<Player*>(s_Current) != NULL)
							{
								dynamic_cast<Player*>(s_Current)->LoadShield();
							}
						}
						break;
					}
				}
			}
			delete s_Current;
			m_GameObjects.erase(m_GameObjects.begin() + i);
		}
	}

	if (m_PowerUpAttack == true)
	{
		for (int i = m_GameObjects.size() - 1; i >= 0; i--)
		{
			GameObject* s_Current = m_GameObjects[i];

			if (dynamic_cast<Asteroid*>(s_Current) != NULL)
			{
				dynamic_cast<Asteroid*>(s_Current)->DestroyedByPowerUp();
				dynamic_cast<Asteroid*>(s_Current)->Destroy();
			}
		}
		m_PowerUpAttack = false;
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

void PlayState::SetUpText()
{
	m_GameTimerText.setFont(m_Font);
	m_GameTimerText.setCharacterSize(30);
	m_GameTimerText.setFillColor(sf::Color::White);
	m_GameTimerText.setPosition(sf::VideoMode::getDesktopMode().width / 25.0f, sf::VideoMode::getDesktopMode().height / 80.0f);

	std::stringstream s_SStream;
	s_SStream << "Game Timer: " << m_GameTimer;
	m_GameTimerText.setString(s_SStream.str());

	m_LevelText.setFont(m_Font);
	m_LevelText.setCharacterSize(30);
	m_LevelText.setFillColor(sf::Color::White);
	m_LevelText.setPosition(sf::VideoMode::getDesktopMode().width / 4.5f, sf::VideoMode::getDesktopMode().height / 30.0f);

	std::stringstream s_sstream;
	s_sstream << "Level: " << m_LevelTracker;
	m_LevelText.setString(s_sstream.str());
}


void PlayState::UpdateGameTime(float GameTimer)
{
	if (m_GameTimer != m_MaxGameTime)
	{
		m_ssGameTimerText.str(std::string());
		m_ssGameTimerText << "Game Timer: " << std::fixed << std::setprecision(2) << m_GameTimer;
		m_GameTimerText.setString(m_ssGameTimerText.str());
	}
}

void PlayState::Draw(sf::RenderWindow* Window)
{
	for (unsigned int i = 0; i < m_GameObjects.size(); i++)
	{
		GameObject* s_Current = m_GameObjects[i];
		s_Current->Draw(Window);
	}

	Window->draw(m_GameTimerText);
	Window->draw(m_LevelText);
	m_Leaderboard->Draw(Window);
}

void PlayState::OnEnter()
{
	m_GameObjects.clear();
	SpawnAsteroids(m_LevelTracker);
	m_TimeUntilRespawn = 2.0f;
	m_RespawnTime = m_TimeUntilRespawn;
	m_Leaderboard->LoadScores();
}

void PlayState::OnExit()
{
	m_ScoreTracker = 0;
	m_LevelTracker = 1;
	m_LevelText.setString(std::string());
	m_ssLevelText << "Level: " << m_LevelTracker;
	m_LevelText.setString(m_ssLevelText.str());
	m_ProceedLevel = false;
	m_IsGameOver = false;
	m_PowerUpSpawned = false;
	m_PowerUpAttack = false;
	m_GameTimer = 60.0f;
	m_PowerUpTimer = 10.0f;
}

void PlayState::AddObject(GameObject* Object)
{
	// Also set the Objects "owner" variable
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
			LargeAsteroid* s_NewAsteroid = new LargeAsteroid(sf::Vector2f(g_RandomLocationX(g_RandomGenerator2), g_RandomLocationY(g_RandomGenerator2)), m_SoundManager, m_TextureManager);
			s_NewAsteroid->SetVelocity(g_RandomSpeed(g_RandomGenerator2));
			AddObject(s_NewAsteroid);
		}
	}
	if (m_ProceedLevel == true)
	{
		for (int i = 0; i < 5 + Level; i++)
		{
			LargeAsteroid* s_NewAsteroid = new LargeAsteroid(sf::Vector2f(g_RandomLocationX(g_RandomGenerator2), g_RandomLocationY(g_RandomGenerator2)), m_SoundManager, m_TextureManager);
			s_NewAsteroid->SetVelocity(g_RandomSpeed(g_RandomGenerator2));
			AddObject(s_NewAsteroid);
		}
		m_ProceedLevel = false;
	}
}

void PlayState::SpawnPowerUps(int Type)
{

}