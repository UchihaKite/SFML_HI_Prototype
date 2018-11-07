#include "PlayState.h"
#include "StateMachine.h"
/*^ This is included to avoid the "pointer to incomplete class type"
error, as a result of forward declaring the StateMachine.*/

#include <iostream>

PlayState::PlayState(StateMachine* Machine, Engine* Engine) :
	GameState(Machine, Engine),
	m_ScoreTracker(0)
{
	m_ScoreManager = new ScoreManager();
}

void PlayState::Update(sf::RenderWindow* Window, float DeltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		//m_Machine->ChangeState("");
		std::cout << "Works" << std::endl;
	}

	m_ScoreManager->Update(m_ScoreTracker);
}

void PlayState::Draw(sf::RenderWindow* Window)
{
	m_ScoreManager->Draw(Window);
}

void PlayState::OnEnter()
{
	
}

void PlayState::OnExit()
{
	m_ScoreManager->StoreHighScore(m_ScoreTracker);
}

void PlayState::AddObject(GameObject* Object)
{
	// Also set thhe Objects "owner" variable
	Object->SetOwner(this);
	m_GameObjects.push_back(Object);
}

void PlayState::UpdateScore(int Score)
{
	m_ScoreTracker += Score;
}