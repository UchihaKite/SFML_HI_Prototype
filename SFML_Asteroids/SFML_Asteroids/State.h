#pragma once
#include <SFML/Graphics.hpp>

class StateMachine; // Forward Declaration

class State
{
public:
	State(StateMachine* Machine);

	virtual void Update(sf::RenderWindow* Window, float DeltaTime);
	virtual void Draw(sf::RenderWindow* Window);
	virtual void OnEnter(); // Behavior Performed as you Enter the State
	virtual void OnExit(); // Cleanup Behavior or Anything Else that is Needed to be Done before State Change
protected:
	StateMachine* m_Machine; // Pointer to the StateMachine
};