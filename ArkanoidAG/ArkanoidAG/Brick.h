#pragma once
#include "Rect.h"
#include "ScoreManager.h"


class Brick : public Rect
{
private:
	static Texture* m_texture_FullLife;
	static Texture* m_texture_HalfLife;
	int m_scoreValue = 0;
	ScoreManager* m_ScoreManager;
public:
	static const int BWIDTH = 32;
	static const int BHEIGHT = 16;
	
	enum LIFEBRICK { FULL, HALF, DEAD };
	LIFEBRICK life;
	Brick(Vec2* position, LIFEBRICK i_life, ScoreManager* i_scoreManager);
	void display(SpriteBatchAlias& i_spriteBatch, VertexDrawer& i_Drawer) override;
	static void setupTexture(Texture* i_FullLifeTexture, Texture* i_HalfLifeTexture);
	static void Reset();
	bool isAlive();
	void hit();

};