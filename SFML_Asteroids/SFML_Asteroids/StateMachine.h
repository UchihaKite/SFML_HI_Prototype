#pragma once
#include "State.h"
#include <vector>
#include <map>

/*
Implemented to take in States with a String Identifier
Uses a Vector for Popping Irrelevant States
*/

class StateMachine
{
public:
	StateMachine();

	void Update(sf::RenderWindow* Window, float DeltaTime);
	void Draw(sf::RenderWindow* Window);

	// Add States to the StateMachine
	void ChangeState(std::string StateName);
	void AddState(std::string StateName, State* State);

	// Add States to the Stack
	void PushState(std::string Name);
	void PopState();

private:
	State * m_CurrentState; // Mark Current State for Updates and Renders
	std::map<std::string, State*> m_States; // Map of all States and their Identifiers
	std::vector<State*> m_StateStack; // Stack for Pushing in New States
};