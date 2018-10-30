#include "StarParticleSystem.h"

Star::Star(sf::Uint16 PositionX, sf::Uint16 PositionY)
{
	m_PositionX = PositionX;
	m_PositionY = PositionY;
}

sf::Uint16 Star::GetPositionX()
{
	return m_PositionX;
}

sf::Uint16 Star::GetPositionY()
{
	return m_PositionY;
}

void Star::SetPositionX(sf::Uint16 PositionX)
{
	m_PositionX = PositionX;
}

void Star::SetPositionY(sf::Uint16 PositionY)
{
	m_PositionY = PositionY;
}

void Star::AddPositionY(sf::Uint16 PositionY)
{
	m_PositionY += PositionY;
}

Starfield::Starfield(sf::RenderWindow* Window)
	: m_MaxSmallStars(0), m_MaxMediumStars(0), m_MaxLargeStars(0), m_WindowSizeX(Window->getSize().x), m_WindowSizeY(Window->getSize().y)
	, m_SmallStarSize(1), m_MediumStarSize(2), m_LargeStarSize(4)
{
	sf::Uint16 s_WindowSizeY = m_WindowSizeY / 10;

	/*
	Create an Image that will be used to create the Textures
	that are used to create the Sprites for our Stars
	*/
	m_SmallStarImage.create(m_SmallStarSize, m_SmallStarSize, sf::Color::White);
	m_MediumStarImage.create(m_MediumStarSize, m_MediumStarSize, sf::Color::White);
	m_LargeStarImage.create(m_LargeStarSize, m_LargeStarSize, sf::Color::White);

	/*
	Create the Seeds and Ranges for our Random Number Generator
	*/
	m_StarGeneratorX.seed(time(0));
	m_StarGeneratorY.seed(time(0) + (s_WindowSizeY / 3));
	m_StarDistributionX = std::uniform_int_distribution<int>(0, m_WindowSizeX);
	m_StarDistributionY = std::uniform_int_distribution<int>(0, m_WindowSizeY);

	/*
	A formula used to generate a maximum number 
	of each size of stars. It will assure we don't have
	too many stars on the screen, reworked to adjust to any resolution
	of a monitor. 
	*/
	m_MaxSmallStars = (m_WindowSizeX / (m_WindowSizeY / 9)) * m_WindowSizeY / (s_WindowSizeY / 9);
	m_MaxMediumStars = (m_WindowSizeX / (m_WindowSizeY / 3)) * m_WindowSizeY / (s_WindowSizeY / 3);
	m_MaxLargeStars = (m_WindowSizeX / m_WindowSizeY) * (m_WindowSizeY / s_WindowSizeY);

	/*
	Using our Random Number Generator as the Parameters
	of newly inititlized Star Classes, store the values
	in our vectors
	*/
	while (m_SmallStars.size() <= m_MaxSmallStars)
	{
		m_SmallStars.push_back(Star(m_StarDistributionX(m_StarGeneratorX), m_StarDistributionY(m_StarGeneratorY)));
	}

	while (m_MediumStars.size() <= m_MaxMediumStars)
	{
		m_MediumStars.push_back(Star(m_StarDistributionX(m_StarGeneratorX), m_StarDistributionY(m_StarGeneratorY)));
	}

	while (m_LargeStars.size() <= m_MaxLargeStars)
	{
		m_LargeStars.push_back(Star(m_StarDistributionX(m_StarGeneratorX), m_StarDistributionY(m_StarGeneratorY)));
	}
}

void Starfield::Update(sf::RenderWindow* Window, float DeltaTime)
{
	/*
	Move the Stars
	*/
	for_each(m_SmallStars.begin(), m_SmallStars.end(), [&](Star& s_Star) 
	{
		s_Star.AddPositionY(1);
	});

	for_each(m_MediumStars.begin(), m_MediumStars.end(), [&](Star& s_Star) 
	{
		s_Star.AddPositionY(2);
	});

	for_each(m_LargeStars.begin(), m_LargeStars.end(), [&](Star& s_Star) 
	{
		s_Star.AddPositionY(4);
	});

	/*
	Remove Star from Vector if it leaves the Window
	*/
	m_SmallStars.erase(remove_if(m_SmallStars.begin(), m_SmallStars.end(), [&](Star& s_Star) 
	{
		return (s_Star.GetPositionY() > m_WindowSizeY);
	}), m_SmallStars.end());

	m_MediumStars.erase(remove_if(m_MediumStars.begin(), m_MediumStars.end(), [&](Star& s_Star) 
	{
		return (s_Star.GetPositionY() > m_WindowSizeY);
	}), m_MediumStars.end());

	m_LargeStars.erase(remove_if(m_LargeStars.begin(), m_LargeStars.end(), [&](Star& s_Star) 
	{
		return (s_Star.GetPositionY() > m_WindowSizeY);
	}), m_LargeStars.end());

	/*
	If a Vector is not Maxed Out, create
	additional stars to fill up the vector
	*/
	while ((int)m_SmallStars.size() <= m_MaxSmallStars)
	{
		m_SmallStars.push_back(Star(m_StarDistributionX(m_StarGeneratorX), 0));
	}

	while ((int)m_MediumStars.size() <= m_MaxMediumStars)
	{
		m_MediumStars.push_back(Star(m_StarDistributionX(m_StarGeneratorX), 0));
	}

	while ((int)m_LargeStars.size() <= m_MaxLargeStars)
	{
		m_LargeStars.push_back(Star(m_StarDistributionX(m_StarGeneratorX), 0));
	}
}

void Starfield::Draw(sf::Texture& Texture)
{
	/*
	Technically nothing is being drawn here.
	What's happening is this.
	You created an "Image" in main
	You create more "Images" from within this class
	These "Images" are being "drawn" onto the
	"Image" that is in the Main Function

	P.S. I'll think of a better way to explain this and update the comment later
	*/
	for (std::vector<Star>::iterator it = m_SmallStars.begin(); it != m_SmallStars.end(); ++it)
	{
		if (it->GetPositionY() < m_WindowSizeY)
		{
			Texture.update(m_SmallStarImage, it->GetPositionX(), it->GetPositionY());
		}
	}

	for (std::vector<Star>::iterator it = m_MediumStars.begin(); it != m_MediumStars.end(); ++it)
	{
		if (it->GetPositionY() < m_WindowSizeY - 1)
		{
			Texture.update(m_MediumStarImage, it->GetPositionX(), it->GetPositionY());
		}
	}

	for (std::vector<Star>::iterator it = m_LargeStars.begin(); it != m_LargeStars.end(); ++it)
	{
		if (it->GetPositionY() < m_WindowSizeY - 2)
		{
			Texture.update(m_LargeStarImage, it->GetPositionX(), it->GetPositionY());
		}
	}
}