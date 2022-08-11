#pragma once
#include "Ball.h"
#include "Vec2.h"
#include "Rectf.h"
#include "Graphics.h"
#include "Colors.h"
#include "Keyboard.h"

class Paddle
{
public:
	Paddle(const Vec2& pos_in, float halfWidth_in, float halfHeight_in);
	void Draw(Graphics& gfx);
	void Update(Keyboard& kbd,float dt);
	bool DoBallCollision(Ball& ball)const;
	void DoWallCollision(const Rectf& walls);
	Rectf GetRect()const;
private:
	static constexpr float wingWidth = 10.0f;
	Color wing = Colors::Red;
	Color pad = Colors::White;
	float speed = 400.0f;
	float halfWidth;
	float halfHeight;
	Vec2 pos;
};