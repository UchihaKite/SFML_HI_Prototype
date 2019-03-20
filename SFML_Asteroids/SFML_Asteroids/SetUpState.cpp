#include "SetUpState.h"

#include "StateMachine.h"
/*^ This is included to avoid the "pointer to incomplete class type"
error, as a result of forward declaring the StateMachine.*/

SetUpState::SetUpState(StateMachine* Machine, Engine* Engine, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager, std::shared_ptr<int> NumPlayers) :
	GameState(Machine, Engine, SoundManager, TextureManager),
	m_NumPlayers(NumPlayers),
	m_KeyPressLimiter(false)
{
	// Load the File for the Font
	m_Font.loadFromFile("Game Assets/Font/kenpixel_high_square.ttf");

	m_TitleText.setFont(m_Font);
	m_TitleText.setCharacterSize(100);
	m_TitleText.setFillColor(sf::Color::White);
	/*
	Make the Text dynamic to whatever the size of the window is
	*/
	m_TitleText.setPosition(sf::VideoMode::getDesktopMode().width / 35.0f, sf::VideoMode::getDesktopMode().height / 5.25f);
	m_TitleText.setString("Asteroids Tournament Mode");

	m_PlayerText.setFont(m_Font);
	m_PlayerText.setCharacterSize(50);
	m_PlayerText.setFillColor(sf::Color::White);
	m_PlayerText.setPosition(sf::VideoMode::getDesktopMode().width / 8.0f, sf::VideoMode::getDesktopMode().height / 2.5f);
	m_ssAmount << "How Many Players?: " << *m_NumPlayers;
	m_PlayerText.setString(m_ssAmount.str());
}

void SetUpState::Update(sf::RenderWindow* Window, float DeltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		m_Machine->ChangeState("RoundState");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_KeyPressLimiter == false)
	{
		m_KeyPressLimiter = true;

		*m_NumPlayers += 1;
		m_ssAmount.str(std::string());
		m_ssAmount << "How Many Players?: " << *m_NumPlayers;
		m_PlayerText.setString(m_ssAmount.str());
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_KeyPressLimiter == true)
	{
		m_KeyPressLimiter = false;
	}
}

void SetUpState::Draw(sf::RenderWindow* Window)
{
	Window->draw(m_PlayerText);
	Window->draw(m_TitleText);
}

void SetUpState::OnEnter()
{
}

void SetUpState::OnExit()
{
	*m_NumPlayers = 0;
	m_ssAmount.str(std::string());
}