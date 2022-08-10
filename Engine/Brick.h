#pragma once
#include "Rectf.h"
#include "Graphics.h"
#include "Colors.h"
#include "Ball.h"

class Brick
{
public:
	Brick(const Rectf& rect_in, Color color_in);
	void Draw(Graphics& gfx)const;
	bool DoBallCollision(Ball& ball);
private:
	Rectf rect;
	Color color;
	bool destroyed = false;
};
