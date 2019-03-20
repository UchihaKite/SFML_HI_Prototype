#include "Engine.h"
#include "TitleScreenState.h"
#include "PlayState.h"
#include "GameOverState.h"
#include "SetUpState.h"
#include "RoundState.h"
#include "TPlayState.h"

Engine::Engine(std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager, std::shared_ptr<int> NumPlayers)
	:
	m_SoundManager(SoundManager),
	m_TextureManager(TextureManager),
	m_NumPlayers(NumPlayers)
{
	m_StateMachine = new StateMachine();
	m_StateMachine->AddState("TitleScreenState", new TitleScreenState(m_StateMachine, this, m_SoundManager, m_TextureManager));
	m_StateMachine->AddState("PlayState", new PlayState(m_StateMachine, this, m_SoundManager, m_TextureManager));
	m_StateMachine->AddState("GameOverState", new GameOverState(m_StateMachine, this, m_SoundManager, m_TextureManager));
	m_StateMachine->AddState("SetUpState", new SetUpState(m_StateMachine, this, m_SoundManager, m_TextureManager, m_NumPlayers));
	m_StateMachine->AddState("RoundState", new RoundState(m_StateMachine, this, m_SoundManager, m_TextureManager, m_NumPlayers));
	m_StateMachine->AddState("TPlayState", new TPlayState(m_StateMachine, this, m_SoundManager, m_TextureManager, m_NumPlayers));
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