#include "TitleScreenState.h"
#include "StateMachine.h"
/*^ This is included to avoid the "pointer to incomplete class type"
error, as a result of forward declaring the StateMachine.*/

#include <iostream>

TitleScreenState::TitleScreenState(StateMachine* Machine, Engine* Engine) :
	GameState(Machine, Engine)
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
	m_TitleText.setString("Asteroids");

	m_StartText.setFont(m_Font);
	m_StartText.setCharacterSize(50);
	m_StartText.setFillColor(sf::Color::White);
	m_StartText.setPosition(sf::VideoMode::getDesktopMode().width / 6.0f, sf::VideoMode::getDesktopMode().height / 2.5f);
	m_StartText.setString("Press Enter to Play");
}

void TitleScreenState::Update(sf::RenderWindow* Window, float DeltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		m_Machine->ChangeState("PlayState");
	}
}

void TitleScreenState::Draw(sf::RenderWindow* Window)
{
	Window->draw(m_StartText);
	Window->draw(m_TitleText);
}

void TitleScreenState::OnEnter()
{
}

void TitleScreenState::OnExit()
{
}