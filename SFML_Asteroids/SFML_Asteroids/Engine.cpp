#include "Engine.h"
#include "TitleScreenState.h"
#include "PlayState.h"
#include "GameOverState.h"

Engine::Engine(std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager)
{
	m_SoundManager = SoundManager;
	m_TextureManager = TextureManager;

	m_StateMachine = new StateMachine();
	m_StateMachine->AddState("TitleScreenState", new TitleScreenState(m_StateMachine, this, m_SoundManager, m_TextureManager));
	m_StateMachine->AddState("PlayState", new PlayState(m_StateMachine, this, m_SoundManager, m_TextureManager));
	m_StateMachine->AddState("GameOverState", new GameOverState(m_StateMachine, this, m_SoundManager, m_TextureManager));
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