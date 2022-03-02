#pragma once


class GameManager
{
private:
	int m_Score = 0;
	int m_Lives = 0;

public:
	void addPoints(int points);
	bool loseLife();
};