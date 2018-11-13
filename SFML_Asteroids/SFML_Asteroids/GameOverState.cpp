#include "GameOverState.h"
#include "StateMachine.h"
/*^ This is included to avoid the "pointer to incomplete class type"
error, as a result of forward declaring the StateMachine.*/

GameOverState::GameOverState(StateMachine* Machine, Engine* Engine) :
	GameState(Machine, Engine),
	m_Timer(0.0f)
{
	// Load the File for the Font
	m_Font.loadFromFile("Game Assets/Font/kenpixel_high_square.ttf");

	m_GameOverText.setFont(m_Font);
	m_GameOverText.setCharacterSize(100);
	m_GameOverText.setFillColor(sf::Color::White);
	/*
	Make the Text dynamic to whatever the size of the window is
	*/
	m_GameOverText.setPosition(sf::VideoMode::getDesktopMode().width / 6.0f, sf::VideoMode::getDesktopMode().height / 5.25f);
	m_GameOverText.setString("GAME OVER");
}

void GameOverState::Update(sf::RenderWindow* Window, float DeltaTime)
{
	m_Timer += DeltaTime;
	if (m_Timer >= 10.0f)
	{
		m_Machine->ChangeState("TitleScreenState");
	}
}

void GameOverState::Draw(sf::RenderWindow* Window)
{
	Window->draw(m_GameOverText);
}

void GameOverState::OnEnter()
{
	m_Timer = 0.0f;
}

void GameOverState::OnExit()
{

}