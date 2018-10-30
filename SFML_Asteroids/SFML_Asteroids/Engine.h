#pragma once
#include <SFML/Graphics.hpp>

class Engine
{
public:
	Engine();
	~Engine();

	void Update(sf::RenderWindow* Window, float DeltaTime); // Update Engine Internals
	void Draw(sf::RenderWindow* Window); // Draw Everything lol
private:

};