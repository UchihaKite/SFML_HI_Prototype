#include "GameState.h"
#include "Engine.h"
#include "TextureHolder.h"

GameState::GameState(StateMachine* Machine, Engine* Engine, SoundContainer* SoundContainer, TextureHolder* TextureHolder) :
	State(Machine),
	m_Engine(Engine),
	m_SoundContainer(SoundContainer),
	m_TextureHolder(TextureHolder)
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