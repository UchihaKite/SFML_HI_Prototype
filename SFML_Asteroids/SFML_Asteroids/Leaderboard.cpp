#include "Leaderboard.h"
#include <set>
#include <functional>
#include <iostream>

Leaderboard::Leaderboard(std::string FileName) :
	ScoreManager("Game Assets/GameData/Score.txt"),
	m_SecondLoad(false),
	m_InputNeeded(false),
	m_MadeIt(0),
	m_Counter(0),
	m_Choice(0),
	m_KeyPressLimiter(0.0f)
{
	SetUpText();
	std::ifstream L("Game Assets/Config/Letters.ini"); //File to be Read From
/*
If the File was Created Correctly and Opened,
Store the Data in the File into the Variables.
The Order DOES Matter.
*/
	if (L.is_open()) //Open the File
	{
		int Key = 0;
		char SecondKey = ' ';

		while (L >> Key >> SecondKey)
		{
			m_Keys[Key] = SecondKey;
		}
	}
	L.close();
}

void Leaderboard::SetUpText()
{
	ScoreManager::SetUpText();

	m_Info.setFont(m_Font);
	m_Info.setCharacterSize(100);
	m_Info.setFillColor(sf::Color::White);
	/*
	Make the Text dynamic to whatever the size of the window is
	*/
	m_Info.setPosition(sf::VideoMode::getDesktopMode().width / 6.0f, sf::VideoMode::getDesktopMode().height / 5.25f);
	m_Info.setString("Made it to Top Ten! \nEnter Name: ");

	m_Name.setFont(m_Font);
	m_Name.setCharacterSize(100);
	m_Name.setFillColor(sf::Color::White);
	m_Name.setPosition(sf::VideoMode::getDesktopMode().width / 6.0f, sf::VideoMode::getDesktopMode().height / 3.25f);

	std::stringstream s_SStream;
	s_SStream << "_" << m_Score;
	m_Name.setString(s_SStream.str());
}

void Leaderboard::Update(int Score)
{
	ScoreManager::Update(Score);

	if (m_InputNeeded == true)
	{
		InputName();
		if (m_Counter >= 10)
		{
			m_InputNeeded = false;
			m_Counter = 0;
			m_Data[m_Tag] = m_MadeIt;
			SortScores();
		}
	}
}

void Leaderboard::Draw(sf::RenderWindow* Window)
{
	ScoreManager::Draw(Window);

	if (m_InputNeeded == true)
	{
		Window->draw(m_Info);
		Window->draw(m_Name);
	}
}

void Leaderboard::StoreHighScore(int Score)
{
	ScoreManager::StoreHighScore(Score);

	for (auto element : m_Data)
	{
		std::cout << "Should draw" << std::endl;
		if (Score > element.second)
		{
			m_InputNeeded = true;
			m_MadeIt = Score;
			break;
		}
	}

	if (m_InputNeeded == true)
	{
		std::map<std::string, int>::iterator IT;

		IT = m_Data.end();

		--IT;
		m_Data.erase(IT);
	}
}

void Leaderboard::LoadScores()
{
	if (m_SecondLoad == true)
	{
		m_Data.clear();
		std::cout << "HELLO " << std::endl;
	}

	std::ifstream LS("Game Assets/GameData/LeaderboardScores.txt"); //File to be Read From
/*
If the File was Created Correctly and Opened,
Store the Data in the File into the Variables.
The Order DOES Matter.
*/
	if (LS.is_open()) //Open the File
	{
		std::string Key = "";
		int SecondKey = 0;

		while (LS >> Key >> SecondKey)
		{
			m_Data[Key] = SecondKey;
		}
	}

	LS.close(); //Close the File

	if (m_SecondLoad == false)
	{
		m_SecondLoad = true;
	}
}

void Leaderboard::SortScores()
{
	// Declaring the type of Predicate that Accepts 2 pairs and returns a Bool
	typedef std::function<bool(std::pair<std::string, int>, std::pair<std::string, int>)> Comparator;

	// Defining a Lambda Function to Compare Two Pairs. It will Compare using the Second Field
	Comparator compFunctor =
		[](std::pair<std::string, int> elem1, std::pair<std::string, int> elem2)
	{
		return elem1.second > elem2.second;
	};

	// Declaring a Set that will Store the Pairs using Comparision Logic
	std::set<std::pair<std::string, int>, Comparator> Set(
		m_Data.begin(), m_Data.end(), compFunctor);

	std::ofstream s_OutputFile("Game Assets/GameData/LeaderboardScores.txt");

	// Iterate over the Set using Range Base
	// It will Print the Items in Sorted Order of Values
	for (std::pair<std::string, int> element : Set)
	{
		s_OutputFile << element.first << " " << element.second << std::endl;
	}

	s_OutputFile.close();
}

void Leaderboard::InputName()
{
	if (m_Counter <= 10)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_KeyPressLimiter >= 2.0f)
		{
			m_KeyPressLimiter = true;

			m_Choice += 1;
			if (m_Choice == 27)
			{
				m_Choice = 0;
			}

			m_KeyPressLimiter = 0.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && m_KeyPressLimiter >= 2.0f)
		{
			m_Input.str(std::string());
			m_Tag += m_Keys.at(m_Choice);
			m_Input << m_Tag;
			m_Name.setString(m_Input.str());
			m_Choice = 0;
			m_Counter++;

			m_KeyPressLimiter = 0.0f;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_KeyPressLimiter < 2.0f)
		{
			m_KeyPressLimiter++;
		}
	}
}