#include "Brick.h"

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

bool Brick::DoBallCollision(Ball& ball)
{
	if (!destroyed && rect.isOverLappingWith(ball.GetRect()))
	{
		const Vec2 ballPos = ball.GetBallPos();
		if (ballPos.x > rect.left && ballPos.x < rect.right)
		{
			ball.ReboundY();
		}
		else
		{
			ball.ReboundX();
		}
		destroyed = true;
		return true;
	}
	return false;
}
