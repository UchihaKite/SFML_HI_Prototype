#pragma once
#include "GameState.h"
#include <sstream>

class RoundState : public GameState
{
public:
	RoundState(StateMachine* Machine, Engine* Engine, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager, std::shared_ptr<int> NumPlayers);

	void Update(sf::RenderWindow* Window, float DeltaTime);
	void Draw(sf::RenderWindow* Window);

	void OnEnter();
	void OnExit();

private:
	sf::Font m_Font;
	sf::Text m_StartText;
	sf::Text m_TitleText;

	std::stringstream m_ssPlayer;
	std::stringstream m_ssRound;
	std::shared_ptr<int> m_NumPlayers;
	int m_Counter; // Delete when you switch to std::map for the players
	float m_BlockEnter;
};