#include "pch.h"
#include "ScoreManager.h"

std::unique_ptr<DirectX::SpriteFont>* ScoreManager::m_font;

void ScoreManager::addPoints(int points)
{
	m_Score += points;
}

void ScoreManager::displayPoints(SpriteBatchAlias& i_spriteBatch)
{
	const wchar_t* output = L"Score";

	Vec2 origin = (Vec2)m_font->get()->MeasureString(output) / 2.f;

	Vec2 scaleFont = Vec2(0.4f, 0.4f);

	m_font->get()->DrawString(i_spriteBatch.get(), output,
		m_fontPos, DirectX::Colors::White, 0.f, origin, scaleFont);
	
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
