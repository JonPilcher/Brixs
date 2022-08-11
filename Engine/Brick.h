#pragma once
#include "Rectf.h"
#include "Graphics.h"
#include "Colors.h"
#include "Ball.h"

class Brick
{
public:
	Brick() = default;
	Brick(const Rectf& rect_in, Color color_in);
	void Draw(Graphics& gfx)const;
	void ExecuteBallCollision(Ball& ball);
	bool CheckBallCollision(const Ball& ball)const;
	Vec2 GetCenter()const;
private:
	static constexpr float padding = 1.0f;
	Rectf rect;
	Color color;
	bool destroyed = false;
};
