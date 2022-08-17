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
	bool DoBallCollision(Ball& ball);
	void DoWallCollision(const Rectf& walls);
	Rectf GetRect()const;
	void ResetCoolDown();
private:
	static constexpr float wingWidth = 10.0f;
	Color wing = Colors::Red;
	Color pad = Colors::White;
	float speed = 500.0f;
	float halfWidth;
	float halfHeight;
	Vec2 pos;
	bool isCoolDown = false;
	// control the paddle rebound behavior here
	static constexpr float maximumExitRatio = 1.6f;
	static constexpr float fixedZoneWidthRatio = 0.2f;
	// these are derived from above controls
	float exitXFactor;
	float fixedZoneHalfWidth;
	float fixedZoneExitX;
};