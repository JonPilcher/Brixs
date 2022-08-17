#pragma once
#include "RectF.h"
#include "Beveler.h"
#include "Graphics.h"

class Walls
{
public:
	Walls(const Rectf& innerBounds_in, float thickness_in, Color baseColor);
	const Rectf& GetInnerBounds() const;
	void Draw(Graphics& gfx) const;
private:
	Rectf innerBounds;
	float thickness;
	Beveler bev;
};