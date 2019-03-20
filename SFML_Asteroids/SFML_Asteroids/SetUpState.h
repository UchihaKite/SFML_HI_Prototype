#pragma once
#include "GameState.h"
#include <sstream>

class SetUpState : public GameState
{
public:
	SetUpState(StateMachine* Machine, Engine* Engine, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager, std::shared_ptr<int> NumPlayers);

	void Update(sf::RenderWindow* Window, float DeltaTime);
	void Draw(sf::RenderWindow* Window);

	void OnEnter();
	void OnExit();

private:
	sf::Font m_Font;
	sf::Text m_PlayerText;
	sf::Text m_TitleText;

	std::stringstream m_ssAmount;

	std::shared_ptr<int> m_NumPlayers;
	bool m_KeyPressLimiter;

	/*
	Once Hector comes up with a way to enable the input
	of letters (etc) we will switch the method we store
	the amount of players we have to a std::map that will be a std::shared_ptr<>
	the key will be a string that is the players name
	and value will be an int that is the players score
	*/
};