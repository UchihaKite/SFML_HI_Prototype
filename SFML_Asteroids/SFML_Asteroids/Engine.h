#pragma once
#include "StateMachine.h"
#include "TextureHolder.h"

class Engine
{
public:
	Engine(SoundContainer* SoundContainer, TextureHolder* TextureHolder);
	~Engine();

	void Update(sf::RenderWindow* Window, float DeltaTime); // Update Engine Internals
	void Draw(sf::RenderWindow* Window); // Draw Everything lol
private:
	// Instance of the State Machine
	StateMachine* m_StateMachine;

	// Instance of the Utilities
	SoundContainer* m_SoundContainer;
	TextureHolder* m_TextureHolder;
};