#include "RoundState.h"
#include "StateMachine.h"
/*^ This is included to avoid the "pointer to incomplete class type"
error, as a result of forward declaring the StateMachine.*/

#include <iostream>

RoundState::RoundState(StateMachine* Machine, Engine* Engine, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager, std::shared_ptr<int> NumPlayers) :
	GameState(Machine, Engine, SoundManager, TextureManager),
	m_NumPlayers(NumPlayers),
	m_Counter(0),
	m_BlockEnter(0.0f)
{
	// Load the File for the Font
	m_Font.loadFromFile("Game Assets/Font/kenpixel_high_square.ttf");

	m_TitleText.setFont(m_Font);
	m_TitleText.setCharacterSize(100);
	m_TitleText.setFillColor(sf::Color::White);
	/*
	Make the Text dynamic to whatever the size of the window is
	*/
	m_TitleText.setPosition(sf::VideoMode::getDesktopMode().width / 6.0f, sf::VideoMode::getDesktopMode().height / 5.25f);
	m_ssRound << "Round " << m_Counter;
	m_TitleText.setString(m_ssRound.str());

	m_StartText.setFont(m_Font);
	m_StartText.setCharacterSize(50);
	m_StartText.setFillColor(sf::Color::White);
	m_StartText.setPosition(sf::VideoMode::getDesktopMode().width / 6.0f, sf::VideoMode::getDesktopMode().height / 3.5f);
	m_ssPlayer << "Player " << m_Counter << " Get Ready!\nPress Enter to Play";
	m_StartText.setString(m_ssPlayer.str());
}

void RoundState::Update(sf::RenderWindow* Window, float DeltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (m_BlockEnter >= 2.0f)
		{
			m_Machine->ChangeState("TPlayState");
		}
	}

	m_BlockEnter += DeltaTime;
}

void RoundState::Draw(sf::RenderWindow* Window)
{
	Window->draw(m_StartText);
	Window->draw(m_TitleText);
}

void RoundState::OnEnter()
{
	m_Counter++;

	m_ssRound.str(std::string());
	m_ssRound << "Round " << m_Counter;
	m_TitleText.setString(m_ssRound.str());

	m_ssPlayer.str(std::string());
	m_ssPlayer << "Player " << m_Counter << " Get Ready!\nPress Enter to Play";
	m_StartText.setString(m_ssPlayer.str());
}

void RoundState::OnExit()
{
	if (m_Counter == *m_NumPlayers)
	{
		m_Counter = 0;
	}

	m_BlockEnter = 0.0f;
}