#include "Engine.h"
#include "TitleScreenState.h"
#include "PlayState.h"
#include "GameOverState.h"

Engine::Engine()
{
	m_StateMachine = new StateMachine();
	m_StateMachine->AddState("TitleScreenState", new TitleScreenState(m_StateMachine, this));
	m_StateMachine->AddState("PlayState", new PlayState(m_StateMachine, this));
	m_StateMachine->AddState("GameOverState", new GameOverState(m_StateMachine, this));
	m_StateMachine->ChangeState("TitleScreenState");
}

Engine::~Engine()
{
}

void Engine::Update(sf::RenderWindow* Window, float DeltaTime)
{
	m_StateMachine->Update(Window, DeltaTime);
}

void Engine::Draw(sf::RenderWindow* Window)
{
	m_StateMachine->Draw(Window);
}