#pragma once
/*
This is the PlayState for the Tournament Mode of the Game.
*/
#include "PlayState.h"

/*
After testing some stuff out and a lot of debate, I've decided to
keep the member variables in this class, even though they are 
are in the base(parent) class. I'm still not 100% on how the balance
will be different in Tournament mode vs Regular play. If it comes to it
we can remove variables from this class and use the base(parent) ones,
but for now they will each have their own.

Also, various things will have to be updated once Hector is done with
the leaderboard (etc).
*/
class TPlayState : public PlayState
{
public:
	TPlayState(StateMachine* Machine, Engine* Engine, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager, std::shared_ptr<int> NumPlayers);

	void Update(sf::RenderWindow* Window, float DeltaTime);
	void Draw(sf::RenderWindow* Window);

	void OnEnter();
	void OnExit();

	// Add GameObjects to the std::vector
	void AddObject(GameObject* Object);

	void UpdateScore(int Score);
	void UpdateGameTime(float GameTimer);

	// To Spawn Asteroids after Level 1
	void SpawnAsteroids(int Level);

private:
	// Store all GameObjects
	std::vector<GameObject*> m_GameObjects;

	int m_ScoreTracker;
	float m_TimeUntilRespawn;
	float m_RespawnTime;
	int m_LevelTracker;
	bool m_ProceedLevel;
	bool m_IsGameOver;

	// Set Up Text for the GameTimer
	void SetUpText();
	float m_GameTimer;
	float m_MaxGameTime;
	sf::Text m_GameTimerText;
	std::stringstream m_ssGameTimerText;

	sf::Font m_Font;
	std::stringstream m_ssLevelText;
	sf::Text m_LevelText;

	std::unique_ptr<ScoreManager> m_ScoreManager;

	std::shared_ptr<int> m_NumPlayers;
	int m_CurrentPlayer;
};