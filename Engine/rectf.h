#pragma once
#include "Vec2.h"

class Rectf
{
public:
	Rectf() = default;
	Rectf(float left_in, float right_in, float top_in, float bottom_in);
	Rectf(const Vec2& topLeft, const Vec2 bottomRight);
	Rectf(const Vec2 topLeft, float width, float height);
	bool isOverLappingWith(const Rectf& other)const;
public:
	float left;
	float right;
	float top;
	float bottom;
};