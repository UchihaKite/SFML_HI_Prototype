#include "Engine.h"
#include "Instances.h"
#include "StarParticleSystem.h"

// Declare the Resoltuion of the Game
sf::Vector2f g_Resolution(sf::VideoMode::getDesktopMode().width / 2.0f, sf::VideoMode::getDesktopMode().height / 2.0f);

int main()
{
	// Create the Window
	sf::RenderWindow s_Window(sf::VideoMode(g_Resolution.x, g_Resolution.y), "Asteroids!");

	// Hide the Mouse Cursor
	s_Window.setMouseCursorVisible(false);

	// Background Music for the Game
	// Use the SoundContainer
	sf::Sound m_Song = SoundContainer::GetSound("Game Assets/Audio/Song.wav");
	m_Song.setVolume(50); // Adjust the volume first
	m_Song.play();
	m_Song.setLoop(true); // Loop it

	// Delcare Instance of the Engine
	Engine s_Engine;

	sf::Image s_StarImage;
	s_StarImage.create(g_Resolution.x + 4, g_Resolution.y + 4, sf::Color::Black);

	/*
	Do not use the TextureContainer if you are using a "sf::Image"
	variable to initialize your Texture variable
	*/
	sf::Texture s_StarTexture;
	s_StarTexture.loadFromImage(s_StarImage);
	s_StarTexture.setSmooth(false);

	sf::Sprite s_StarSprite;
	s_StarSprite.setTexture(s_StarTexture);
	s_StarSprite.setPosition(0.0f, 0.0f);

	Starfield s_BackgroundStars(&s_Window);

	// Declare a Clock in Order to Obtain the DeltaTime
	sf::Clock s_Clock;
	while (s_Window.isOpen())
	{
		// Store the Time Between Frames
		sf::Time s_Time = s_Clock.restart();
		// Store that Time, As Seconds, into a Float
		float s_DeltaTimeAsSeconds = s_Time.asSeconds();

		sf::Event s_Event;
		while (s_Window.pollEvent(s_Event))
		{
			if (s_Event.type == sf::Event::KeyPressed)
			{
				if (s_Event.key.code == sf::Keyboard::Escape)
				{
					/*
					Make sure you clear the contents contained in "SoundContainer"
					and in TextureHolder. Otherwise, the Program/Game will Crash
					upon trying to Exit
					*/
					TextureHolder::Clear();
					SoundContainer::Clear();
					s_Window.close(); // Press "ESC" to Close the Window/Game
				}
			}

			if (s_Event.type == sf::Event::Closed)
			{
				TextureHolder::Clear();
				SoundContainer::Clear();
				s_Window.close(); // Click the "X" to Close the Window/Game
			}
		}
		s_BackgroundStars.Update(&s_Window, s_DeltaTimeAsSeconds);
		s_StarTexture.loadFromImage(s_StarImage);

		s_Window.clear();
		s_BackgroundStars.Draw(s_StarTexture);
		s_Window.draw(s_StarSprite);
		s_Engine.Update(&s_Window, s_DeltaTimeAsSeconds); // Update all Internals before Drawing Anything
		s_Engine.Draw(&s_Window); // Draw all Internals
		s_Window.display();
	}
	return 0;
}