#pragma once
#include "Rectf.h"
#include "Graphics.h"
#include "Colors.h"

class Brick
{
public:
	Brick(const Rectf& rect_in, Color color_in);
	void Draw(Graphics& gfx)const;

private:
	Rectf rect;
	Color color;
	bool distroyed = false;
};
