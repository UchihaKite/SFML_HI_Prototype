#include "ScoreManager.h"
#include <iostream>

ScoreManager::ScoreManager() :
	m_Score(0),
	m_HighScore(0)
{
	SetUpText();
}

void ScoreManager::SetUpText()
{
	/*
	Depending on the project, the parameters may need to be changed
	to adjust to it, but in general this is
	all you need
	*/

	// Load the File for the Font
	m_Font.loadFromFile("Game Assets/Font/kenpixel_high_square.ttf");

	m_ScoreText.setFont(m_Font);
	m_ScoreText.setCharacterSize(30);
	m_ScoreText.setFillColor(sf::Color::White);
	m_ScoreText.setPosition(sf::VideoMode::getDesktopMode().width / 25.0f, sf::VideoMode::getDesktopMode().height / 30.0f);

	std::stringstream s_SStream;
	s_SStream << "Score: " << m_Score;
	m_ScoreText.setString(s_SStream.str());

	std::ifstream s_InputFile("Game Assets/GameData/Score.txt");
	/*
	If the File is Open (If the file doesn't exist, it'll be created)
	then take the content of the file and store it in
	"m_HighScore".
	And then close the file.
	*/
	if (s_InputFile.is_open())
	{
		s_InputFile >> m_HighScore;
		s_InputFile.close();
	}

	m_HighScoreText.setFont(m_Font);
	m_HighScoreText.setCharacterSize(30);
	m_HighScoreText.setFillColor(sf::Color::White);
	m_HighScoreText.setPosition(sf::VideoMode::getDesktopMode().width / 2.5f, sf::VideoMode::getDesktopMode().height / 30.0f);

	/*
	Can be used to store a "string" and an "int" together.
	Then returned, together, as a single "string"
	using the function ".str()"
	*/
	std::stringstream s_Stream;
	s_Stream << "Highscore: " << m_HighScore;
	m_HighScoreText.setString(s_Stream.str());
}

void ScoreManager::Update(int Score)
{
	if (m_Score != Score)
	{
		m_Score = Score;
		m_ssScore.str(std::string());
		m_ssScore << "Score: " << m_Score;
		m_ScoreText.setString(m_ssScore.str());
	}

	if (m_Score > m_HighScore)
	{
		m_HighScore = m_Score;
		m_ssHighScore.str(std::string());
		m_ssHighScore << "Highscore: " << m_HighScore;
		m_HighScoreText.setString(m_ssHighScore.str());
	}
}

void ScoreManager::Draw(sf::RenderWindow* Window)
{
	Window->draw(m_ScoreText);
	Window->draw(m_HighScoreText);
}

void ScoreManager::StoreHighScore(int Score)
{
	m_Score = Score;

	if (m_Score >= m_HighScore)
	{
		m_HighScore = m_Score;

		/*
		Save the New Highscore to the File
		*/
		std::ofstream s_OutputFile("Game Assets/GameData/Score.txt");
		s_OutputFile << m_HighScore;
		s_OutputFile.close();
	}
}