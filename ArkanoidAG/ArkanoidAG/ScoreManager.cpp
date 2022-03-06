#include "pch.h"
#include "ScoreManager.h"

std::unique_ptr<DirectX::SpriteFont>* ScoreManager::m_font;

void ScoreManager::addPoints(int points)
{
	m_Score += points;
}

void ScoreManager::resetScore()
{
	m_Score = 0;
}

void ScoreManager::displayPoints(SpriteBatchAlias& i_spriteBatch)
{
	Vec2 scaleFont = Vec2(0.4f, 0.4f);
	const wchar_t* scoreString = L"Score";

	Vec2 scoreStringOrigin = (Vec2)m_font->get()->MeasureString(scoreString) / 2.f;

	

	m_font->get()->DrawString(i_spriteBatch.get(), scoreString,
		m_fontPos, DirectX::Colors::White, 0.f, scoreStringOrigin, scaleFont);

	Vec2 scorePos = Vec2(m_fontPos.x, m_fontPos.y + 25);
	std::string scoreValueString = std::to_string(m_Score);

	Vec2 scoreValueOrigin = (Vec2)m_font->get()->MeasureString(scoreValueString.c_str()) / 2.f;

	m_font->get()->DrawString(i_spriteBatch.get(), scoreValueString.c_str(),
		scorePos, DirectX::Colors::White, 0.f, scoreValueOrigin, scaleFont);
}

void ScoreManager::setPosition(float i_X, float i_Y)
{
	m_fontPos.x = i_X;
	m_fontPos.y = i_Y;
}

void ScoreManager::setupFont(std::unique_ptr<DirectX::SpriteFont>* i_font)
{
	m_font = i_font;
}



void ScoreManager::Reset()
{
	m_font->reset();
}
