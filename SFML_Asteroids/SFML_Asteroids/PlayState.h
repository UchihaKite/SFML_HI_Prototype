#pragma once
#include "GameState.h"
#include "GameObject.h"
#include "ScoreManager.h"

#include <vector>

class PlayState : public GameState
{
public:
	PlayState(StateMachine* Machine, Engine* Engine);

	void Update(sf::RenderWindow* Window, float DeltaTime);
	void Draw(sf::RenderWindow* Window);

	void OnEnter();
	void OnExit();

	// Add GameObjects to the std::vector
	void AddObject(GameObject* Object);
	void UpdateScore(int Score);

	// To Spawn Asteroids after Level 1
	void SpawnAsteroids(int Level);

private:
	// Store all GameObjects
	std::vector<GameObject*> m_GameObjects;
	ScoreManager* m_ScoreManager;
	int m_ScoreTracker;
	int m_LivesRemaining;
	float m_TimeUntilRespawn;
	int m_LevelTracker;
	bool m_ProceedLevel;
	bool m_IsGameOver;

	// For the Sprites that Represent the remaining Lives
	sf::Texture m_LivesTexture;
	sf::Color m_LivesColor;

	sf::Font m_Font;
	sf::Text m_OutcomeText;
	sf::Text m_LevelText;
};