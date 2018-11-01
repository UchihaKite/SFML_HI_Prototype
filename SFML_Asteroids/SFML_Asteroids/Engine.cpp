#include "Engine.h"
#include "TitleScreenState.h"

Engine::Engine()
{
	m_StateMachine = new StateMachine();
	m_StateMachine->AddState("TitleScreen", new TitleScreenState(m_StateMachine, this));
	m_StateMachine->ChangeState("TitleScreen");
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