#pragma once
#include "StateMachine.h"
#include "TextureManager.h"

class Engine
{
public:
	Engine(SoundManager* SoundManager, TextureManager* TextureManager);
	~Engine();

	void Update(sf::RenderWindow* Window, float DeltaTime); // Update Engine Internals
	void Draw(sf::RenderWindow* Window); // Draw Everything lol
private:
	// Instance of the State Machine
	StateMachine* m_StateMachine;

	// Instance of the Utilities
	SoundManager* m_SoundManager;
	TextureManager* m_TextureManager;
};