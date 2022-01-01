#pragma once
#include "Rect.h"

class Brick : public Rect
{


public:
	enum LIFEBRICK { FULL, HALF, DEAD };
	LIFEBRICK life;
	const float BWIDTH = 20;
	const float BHEIGHT = 10;
	void display() override;
	bool isAlive();
	void hit();

};