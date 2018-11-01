#pragma once
#include "SFML/Graphics.hpp"
#include <fstream> // Needed for "std::ifstream" and "std::ofstream"
#include <sstream> // Needed for "std::stringstream"

class ScoreManager
{
public:
	ScoreManager();

	void SetUpText();

	void Update(int Score);
	void Draw(sf::RenderWindow* Window);

	void StoreHighScore(int Score);
private:
	int m_Score;
	int m_HighScore;

	// Variables for Text
	sf::Font m_Font;
	sf::Text m_ScoreText;
	sf::Text m_HighScoreText;

	std::stringstream m_ssScore;
	std::stringstream m_ssHighScore;
};