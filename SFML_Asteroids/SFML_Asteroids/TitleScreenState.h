#pragma once
#include "GameState.h"

class TitleScreenState : public GameState
{
public:
	TitleScreenState(StateMachine* Machine, Engine* Engine);

	void Update(sf::RenderWindow* Window, float DeltaTime);
	void Draw(sf::RenderWindow* Window);

	void OnEnter();
	void OnExit();

private:
	sf::Font m_Font;
	sf::Text m_StartText;
	sf::Text m_TitleText;
};