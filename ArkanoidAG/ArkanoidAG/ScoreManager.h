#pragma once
#include <string>

using SpriteBatchAlias = std::unique_ptr<DirectX::SpriteBatch>;
using Vec2 = DirectX::SimpleMath::Vector2;
using Microsoft::WRL::ComPtr;
using Color = DirectX::XMVECTORF32;


class ScoreManager
{
private:
	int m_Score = 0;
	static std::unique_ptr<DirectX::SpriteFont>* m_font;
	Vec2 m_fontPos;

public:
	void addPoints(int points);
	void resetScore();
	void displayPoints(SpriteBatchAlias& i_spriteBatch);
	void setPosition(float i_X, float i_Y);
	static void setupFont(std::unique_ptr<DirectX::SpriteFont>* i_texture);
	static void Reset();
};