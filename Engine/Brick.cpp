#include "Brick.h"
#include <assert.h>
#include <cmath>


Brick::Brick(const Rectf& rect_in, Color color_in)
	:
	rect(rect_in),
	destroyed(false),
	bev(color_in)
{
}

void Brick::Draw(Graphics& gfx) const
{
	if (!destroyed)
	{
		bev.DrawBeveledBrick(rect.GetExpanded(- padding), bevelSize,gfx);
	}
}

bool Brick::CheckBallCollision(const Ball& ball) const
{
	return !destroyed && rect.isOverLappingWith(ball.GetRect());
}

Vec2 Brick::GetCenter() const
{
	return rect.GetCenter();
}

bool Brick::Destroyed() const
{
	return destroyed;
}

void Brick::ExecuteBallCollision(Ball& ball)
{
	assert(CheckBallCollision(ball));

	const Vec2 ballPos = ball.GetBallPos();
	if (std::signbit(ball.GetVelocity().x) == std::signbit((ballPos - GetCenter()).x))
	{
		ball.ReboundY();
	}
	else if (ballPos.x > rect.left && ballPos.x < rect.right)
	{
		ball.ReboundY();
	}
	else
	{
		ball.ReboundXDist();
	}
	destroyed = true;
	
}
