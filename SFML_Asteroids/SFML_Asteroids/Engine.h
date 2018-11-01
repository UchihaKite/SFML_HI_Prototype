#pragma once
#include "StateMachine.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Update(sf::RenderWindow* Window, float DeltaTime); // Update Engine Internals
	void Draw(sf::RenderWindow* Window); // Draw Everything lol
private:
	// Instance of the State Machine
	StateMachine* m_StateMachine;
};