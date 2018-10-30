#pragma once
#include "State.h"

class Engine; // Forward Declaration

class GameState : public State
{
public:
	GameState(StateMachine* Machine, Engine* Engine);

	virtual void Update(sf::RenderWindow* Window, float DeltaTime);
	virtual void Draw(sf::RenderWindow* Window);
	virtual void OnEnter();
	virtual void OnExit();

	inline Engine* GetEngine() { return m_Engine; }
protected:
	Engine* m_Engine;
};