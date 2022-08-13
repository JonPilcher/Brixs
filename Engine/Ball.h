#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "SpriteCodex.h"

class Ball
{
public:
	Ball(const Vec2& pos_in, const Vec2& vel_in);
	void Draw(Graphics& gfx)const;
	void Update(float dt);
	bool DoWallCollision(const Rectf& walls);
	void ResetBall(const Rectf& walls);
	void ReboundX();
	void ReboundY();
	Rectf GetRect()const;
	Vec2 GetVelocity()const;
	Vec2 GetBallPos()const;
	bool IsGameOver()const;
private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
	static constexpr int nlives = 5;
	int livesUsed = 0;
	bool isGameOver = false;
};