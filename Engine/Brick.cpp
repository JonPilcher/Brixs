#include "Brick.h"
#include <assert.h>
#include <cmath>


Brick::Brick(const Rectf& rect_in, Color color_in)
	:
	rect (rect_in),
	color (color_in)
{
}

void Brick::Draw(Graphics& gfx) const
{
	if (!destroyed)
	{
		gfx.DrawRect(rect.GetExpanded(- padding), color);
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
		ball.ReboundX();
	}
	destroyed = true;
	
}
