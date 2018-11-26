#pragma once
#include "State.h"

class Engine; // Forward Declaration
class SoundContainer;
class TextureHolder;

class GameState : public State
{
public:
	GameState(StateMachine* Machine, Engine* Engine, SoundContainer* SoundContainer, TextureHolder* TextureHolder);

	virtual void Update(sf::RenderWindow* Window, float DeltaTime);
	virtual void Draw(sf::RenderWindow* Window);
	virtual void OnEnter();
	virtual void OnExit();

	inline Engine* GetEngine() { return m_Engine; }
protected:
	Engine* m_Engine;
	SoundContainer* m_SoundContainer;
	TextureHolder* m_TextureHolder;
};