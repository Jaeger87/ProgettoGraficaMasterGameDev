#include "pch.h"
#include "GameManager.h"

void GameManager::addPoints(int points)
{
	m_Score += points;
}

bool GameManager::loseLife()
{
	m_Lives--;
	return m_Lives > 0;
}
