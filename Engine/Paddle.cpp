#include "Paddle.h"

Paddle::Paddle(const Vec2& pos_in, float halfWidth_in, float halfHeight_in)
	:
	pos(pos_in),
	halfWidth(halfWidth_in),
	halfHeight(halfHeight_in)
{
}

void Paddle::Draw(Graphics& gfx)
{
	Rectf rect = GetRect();
	gfx.DrawRect(GetRect(), wing);
	rect.left += wingWidth;
	rect.right -= wingWidth;
	gfx.DrawRect(rect, pad);
}

void Paddle::Update(Keyboard& kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed * dt;
	}
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * dt;
	}
}

bool Paddle::DoBallCollision(Ball& ball) const
{
	if (ball.GetVelocity().y > 0.0f && GetRect().isOverLappingWith(ball.GetRect()))
	{
		ball.ReboundY();
		return true;
	}
	return false;
}

void Paddle::DoWallCollision(const Rectf& walls)
{
	const Rectf rect = GetRect();
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
	}
	else if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right;
	}
}

Rectf Paddle::GetRect() const
{
	return Rectf::FromCenter(pos,halfWidth,halfHeight);
}
