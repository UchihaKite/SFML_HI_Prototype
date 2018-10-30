#include "GameState.h"
#include "Engine.h"

GameState::GameState(StateMachine* Machine, Engine* Engine) :
	State(Machine),
	m_Engine(Engine)
{
	//No behavior for base state
}

void GameState::Update(sf::RenderWindow* Window, float DeltaTime)
{
	//No behavior for base state
}

void GameState::Draw(sf::RenderWindow* Window)
{
	//No behavior for base state
}

void GameState::OnEnter()
{
	//No behavior for base state
}

void GameState::OnExit()
{
	//No behavior for base state
}