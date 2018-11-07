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


private:
	// Store all GameObjects
	std::vector<GameObject*> m_GameObjects;
	ScoreManager* m_ScoreManager;
	int m_ScoreTracker;
};