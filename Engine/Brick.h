#pragma once
#include "Rectf.h"
#include "Graphics.h"
#include "Colors.h"
#include "Ball.h"
#include "Beveler.h"

class Brick
{
public:
	Brick() = default;
	Brick(const Rectf& rect_in, Color color_in);
	void Draw(Graphics& gfx)const;
	void ExecuteBallCollision(Ball& ball);
	bool CheckBallCollision(const Ball& ball)const;
	Vec2 GetCenter()const;
	bool Destroyed()const;
private:
	static constexpr float padding = 0.5f;
	static constexpr int bevelSize = 3;
	Rectf rect;
	Beveler bev;
	bool destroyed = false;
};
