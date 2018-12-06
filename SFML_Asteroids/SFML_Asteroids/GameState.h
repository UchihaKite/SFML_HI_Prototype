#pragma once
#include "State.h"

class Engine; // Forward Declaration
class SoundManager;
class TextureManager;

class GameState : public State
{
public:
	GameState(StateMachine* Machine, Engine* Engine, std::shared_ptr<SoundManager> SoundManager, std::shared_ptr<TextureManager> TextureManager);

	virtual void Update(sf::RenderWindow* Window, float DeltaTime);
	virtual void Draw(sf::RenderWindow* Window);
	virtual void OnEnter();
	virtual void OnExit();

	inline Engine* GetEngine() { return m_Engine; }
protected:
	Engine* m_Engine;
	std::shared_ptr<SoundManager> m_SoundManager;
	std::shared_ptr<TextureManager> m_TextureManager;
};