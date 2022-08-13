#include"Ball.h"
#include "SpriteCodex.h"

Ball::Ball(const Vec2& pos_in, const Vec2& vel_in)
	:
	pos(pos_in),
	vel(vel_in)
{
}

void Ball::Draw(Graphics& gfx) const
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::Update(float dt)
{
	pos += vel * dt;
}

bool Ball::DoWallCollision(const Rectf& walls)
{
	bool Collided = false;
	const Rectf rect = GetRect();

	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
		ReboundX();
		Collided = true;
	}
	else if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right;
		ReboundX();
		Collided = true;
	}
	if (rect.top < walls.top)
	{
		pos.y += walls.top - rect.top;
		ReboundY();
		Collided = true;
	}
	else if (rect.bottom > walls.bottom)
	{
		pos.x = 300.0f;
		pos.y = 300.0f;	
	}
	return Collided;
}

void Ball::ResetBall(const Rectf& walls)
{
	const Rectf rect = GetRect();
	if (rect.bottom > walls.bottom)
	{
		pos.x = 300.0f;
		pos.y = 300.0f;
		
	}
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

Rectf Ball::GetRect() const
{
	return Rectf::FromCenter(pos,radius,radius);
}

Vec2 Ball::GetVelocity() const
{
	return vel;
}

Vec2 Ball::GetBallPos() const
{
	return pos;
}
