#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <ctime>

/*
The "Star" Class is only made up of Locations.
Think of a "sf::Uint16" as a typical "int",
but with a set size. A size lower than the standard
uninitialized "int" variable.
*/
class Star
{
public:
	Star(sf::Uint16 PositionX, sf::Uint16 PositionY);
	sf::Uint16 GetPositionX();
	sf::Uint16 GetPositionY();
	void SetPositionX(sf::Uint16 PositionX);
	void SetPositionY(sf::Uint16 PositionY);
	void AddPositionY(sf::Uint16 PositionY);
private:
	sf::Uint16 m_PositionX;
	sf::Uint16 m_PositionY;
};

class Starfield
{
public:
	Starfield(sf::RenderWindow* Window);
	void Update(sf::RenderWindow* Window, float DeltaTime);
	void Draw(sf::Texture& Texture);

protected:
	/*
	The Maximum number of stars we can have.
	Based on the resultion of the Monitor
	*/
	int m_MaxSmallStars;
	int m_MaxMediumStars;
	int m_MaxLargeStars;

	// Save the Resolution of the Monitor
	sf::Uint16 m_WindowSizeX;
	sf::Uint16 m_WindowSizeY;

	/*
	The Generated Number of Each Size
	of Stars
	*/
	sf::Uint16 m_SmallStarSize;
	sf::Uint16 m_MediumStarSize;
	sf::Uint16 m_LargeStarSize;

	// Store the Location of each Size of Star
	std::vector<Star> m_SmallStars;
	std::vector<Star> m_MediumStars;
	std::vector<Star> m_LargeStars;

	/*
	Rather than Uploading a "jpg or png" image
	to represent our Stars, we can just create
	an "sf::Image" instead
	*/
	sf::Image m_SmallStarImage;
	sf::Image m_MediumStarImage;
	sf::Image m_LargeStarImage;

	/*
	A different want to generate random numbers, I prefer
	this method because it isn't as reliant on the "time",
	and I've found it greatly reduces the amount of duplicate
	numbers you get in a row
	*/
	std::mt19937 m_StarGeneratorX;
	std::mt19937 m_StarGeneratorY;
	std::uniform_int_distribution<int> m_StarDistributionX;
	std::uniform_int_distribution<int> m_StarDistributionY;
};