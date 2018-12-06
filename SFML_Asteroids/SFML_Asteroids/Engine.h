#pragma once
#include "StateMachine.h"
#include "TextureManager.h"

class Engine
{
public:
	Engine(std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager);
	~Engine();

	void Update(sf::RenderWindow* Window, float DeltaTime); // Update Engine Internals
	void Draw(sf::RenderWindow* Window); // Draw Everything lol
private:
	// Instance of the State Machine
	StateMachine* m_StateMachine;

	// Instance of the Utilities
	std::shared_ptr<SoundManager> m_SoundManager;
	std::shared_ptr<TextureManager> m_TextureManager;
};