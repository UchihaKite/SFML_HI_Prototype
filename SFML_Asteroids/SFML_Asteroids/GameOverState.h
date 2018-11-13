#pragma once
#include "GameState.h"

class GameOverState : public GameState
{
public:
	GameOverState(StateMachine* Machine, Engine* Engine);

	void Update(sf::RenderWindow* Window, float DeltaTime);
	void Draw(sf::RenderWindow* Window);

	void OnEnter();
	void OnExit();

private:
	sf::Font m_Font;
	sf::Text m_GameOverText;
	float m_Timer;
};