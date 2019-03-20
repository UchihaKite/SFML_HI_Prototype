#pragma once
#include "ScoreManager.h"

class Leaderboard : public ScoreManager
{
public:
	Leaderboard(std::string FileName);

	virtual void SetUpText();

	virtual void Update(int Score);
	virtual void Draw(sf::RenderWindow* Window);

	virtual void StoreHighScore(int Score);

	void LoadScores();
	void SortScores();

	void InputName();

	inline bool GetInputNeeded() { return m_InputNeeded; }

private:

	std::map<std::string, int> m_Data;
	std::map<std::string, int> m_SortedData;
	std::map<int, char> m_Keys;

	bool m_SecondLoad;
	bool m_InputNeeded;
	float m_KeyPressLimiter;
	int m_MadeIt;
	int m_Counter;
	int m_Choice;

	sf::Text m_Info;
	sf::Text m_Name;
	std::stringstream m_Input;
	std::string m_Tag;
};