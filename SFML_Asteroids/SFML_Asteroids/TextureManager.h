#pragma once
#include "SoundManager.h"
#include <SFML/Graphics.hpp>

/*
Objects will no longer need
sf::Texture Member Variables
They only call TextureManager to Initialize a Sprite
*/

enum TextureType
{
	ASTEROID_SMALL,
	ASTEROID_MED,
	ASTEROID_LARGE,
	BULLET,
	PLAYER,
	//Power-Ups/Bonuses
	BONUS_POINTS,
	ICE_CREAM,
	PLAY_TIME,
	THE_BOMB,
	THE_SHIELD,
	// Alternate Attacks
	BOMB,
	AMOUNT
};

class TextureManager
{
public:
	TextureManager();

	void LoadTextures();
	sf::Texture& ReturnTexture(TextureType Type);
private:
	// Map Paths to Enum
	std::map<TextureType, std::string> m_TextureMap =
	{
		{ASTEROID_SMALL, "Game Assets/Sprites/PNG/Meteors/meteorBrown_small2.png"},
		{ASTEROID_MED, "Game Assets/Sprites/PNG/Meteors/meteorBrown_med1.png"},
		{ASTEROID_LARGE, "Game Assets/Sprites/PNG/Meteors/meteorBrown_big1.png"},
		{BULLET, "Game Assets/Sprites/PNG/Lasers/laserBlue08.png"},
		{PLAYER, "Game Assets/Sprites/PNG/playerShip2_red.png"},
		//Power-Ups/Bonuses
		{BONUS_POINTS, "Game Assets/Sprites/PNG/Power-ups/BonusPoints.png"},
		{ICE_CREAM, "Game Assets/Sprites/PNG/Power-ups/IceCream.png"},
		{PLAY_TIME, "Game Assets/Sprites/PNG/Power-ups/PlayTime.png"},
		{THE_BOMB, "Game Assets/Sprites/PNG/Power-ups/TheBomb.png"},
		{THE_SHIELD, "Game Assets/Sprites/PNG/Power-ups/TheShield.png"},
		// Alternate Attacks
		{BOMB, "Game Assets/Sprites/PNG/Bomb.png"}
	};

	std::map<TextureType, sf::Texture> m_Textures;
};