#pragma once
#include "GameState.h"
#include "GameObject.h"
#include "ScoreManager.h"
#include "Leaderboard.h"

class PlayState : public GameState
{
public:
	PlayState(StateMachine* Machine, Engine* Engine, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager);

	virtual void Update(sf::RenderWindow* Window, float DeltaTime);
	virtual void Draw(sf::RenderWindow* Window);

	virtual void OnEnter();
	virtual void OnExit();

	// Add GameObjects to the std::vector
	virtual void AddObject(GameObject* Object);

	virtual void UpdateScore(int Score);
	virtual void UpdateGameTime(float GameTimer);

	// To Spawn Asteroids after Level 1
	virtual void SpawnAsteroids(int Level);

	// To Spawn Power-Ups
	virtual void SpawnPowerUps(int Type);

protected:
	// Store all GameObjects
	std::vector<GameObject*> m_GameObjects;

	int m_ScoreTracker;
	float m_TimeUntilRespawn;
	float m_RespawnTime;
	int m_LevelTracker;
	bool m_ProceedLevel;
	bool m_IsGameOver;

	// Set Up Text for the GameTimer
	virtual void SetUpText();
	float m_GameTimer;
	float m_MaxGameTime;
	sf::Text m_GameTimerText;
	std::stringstream m_ssGameTimerText;

	sf::Font m_Font;
	std::stringstream m_ssLevelText;
	sf::Text m_LevelText;

	float m_PowerUpTimer;
	bool m_PowerUpSpawned;
	bool m_PowerUpAttack;

private:
	std::unique_ptr<Leaderboard> m_Leaderboard;
};