#pragma once
#include "SpriteCodex.h"
#include "Graphics.h"
#include <algorithm>

class LifeCounter
{
public:
	LifeCounter(Vec2 pos,int lives)
		:
		pos(pos),
		lives(lives)
	{}
	bool ConsumeLife()
	{
		const bool hasLife = lives > 0;
		lives = std::max(lives - 1, 0);
		return hasLife;
	}
	void Draw(Graphics& gfx)const
	{
		const Vec2 offset(spacing, 0.0f);
		for (int c = 0; c < lives; c++)
		{
			SpriteCodex::DrawBall(pos + offset * float(c), gfx);
		}
	}
private:
	static constexpr float spacing = 16;
	int lives;
	Vec2 pos;
};