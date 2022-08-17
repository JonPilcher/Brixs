/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	walls(Rectf::FromCenter(Graphics::GetScreenRect().GetCenter(), fieldWidth / 2.0f, fieldHeight / 2.0f),
		wallThickness, wallColor),
	soundPad(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\arkbrick.wav"),
	soundTitle(L"Sounds\\title.wav"),
	soundYouWin(L"Sounds\\YouWin.wav"),
	soundYouLose(L"Sounds\\YouLose.wav"),
	soundMissedBall(L"Sounds\\missedBall.wav"),
	soundGetReady(L"sounds\\ready.wav"),
	paddle(Vec2(500.0f, 500.0f), 50.0f, 10.0f),
	lifeCounter({160.0f,15},5)
{
	ResetBall();
	const Vec2 gridTopLeft(walls.GetInnerBounds().left, walls.GetInnerBounds().top + topSpace);
	int i = 0;
	for (int y = 0; y < nBricksDown; y++)
	{
		const Color c = brickColors[y];
		for (int x = 0; x < nBricksAcross; x++)
		{
			brick[i] = Brick(Rectf(
				gridTopLeft + Vec2(x * brickWidth, y * brickHeight),
				brickWidth, brickHeight), c);
			i++;
		}
	}
	soundTitle.Play();
}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	if (gameState == 1)
	{
			paddle.Update(wnd.kbd, dt);
			paddle.DoWallCollision(walls.GetInnerBounds());
			ball.Update(dt);

			bool collisionHappened = false;
			float curColDistSq;
			int curColIndex;
			for (int i = 0; i < nBricks; i++)
			{
				if (brick[i].CheckBallCollision(ball))
				{
					const float newColDistSq = (ball.GetBallPos() - brick[i].GetCenter()).GetLengthSq();
					if (collisionHappened)
					{
						if (newColDistSq < curColDistSq)
						{
							curColDistSq = newColDistSq;
							curColIndex = i;
						}
					}
					else
					{
						curColDistSq = newColDistSq;
						curColIndex = i;
						collisionHappened = true;
					}
				}
			}
			bool isDestroyed = true;
			for (int i = 0; i < nBricks; i++)
			{
				isDestroyed = isDestroyed && brick[i].Destroyed();
			}
			if (isDestroyed)
			{
				
				gameState = 4;
				playSound++;
				if (playSound == 1)
				{
					soundYouWin.Play();
				}
					playSound++;
			}

			if (collisionHappened)
			{
				paddle.ResetCoolDown();
				brick[curColIndex].ExecuteBallCollision(ball);
				soundBrick.Play();
			}
			if (paddle.DoBallCollision(ball))
			{
				soundPad.Play();
			}
			const int ballWallColResult = ball.DoWallCollision(walls.GetInnerBounds());
			if (ballWallColResult == 1)
			{
				if (!paddle.GetRect().isOverLappingWith(ball.GetRect()))
				{
					paddle.ResetCoolDown();
				}
				soundPad.Play();
			}
			else if (ballWallColResult == 2)
			{				
				soundMissedBall.Play();
				ResetBall();
				StartRound();
				paddle.ResetCoolDown();
			}
	}
	else if (gameState == 0)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			StartRound();
		}
	}
	else if (gameState == 3)
	{
		if ((curWaitTime += dt) > readyWaitTime)
		{
			gameState = 1;
		}
	}
}

void Game::StartRound()
{
	if (lifeCounter.ConsumeLife())
	{
		curWaitTime = 0.0f;
		gameState = 3;
		soundGetReady.Play();
	}
}

void Game::ResetBall()
{
	ball = Ball(Graphics::GetScreenRect().GetCenter(), Vec2(-0.55f, -1.0f));
}

void Game::ComposeFrame()
{
	if (gameState == 0)
	{
		SpriteCodex::DrawTitle(250, 150, gfx);
		SpriteCodex::DrawStartMessage(250, 300, gfx);
	}
	if(gameState != 0)
	{
		SpriteCodex::DrawWalls(120, 0, gfx);
		SpriteCodex::DrawWalls(640, 0, gfx);
		SpriteCodex::DrawTop(40, 0, gfx);
		lifeCounter.Draw(gfx);
		for (const Brick& b : brick)
		{
			b.Draw(gfx);
		}
		paddle.Draw(gfx);
	}
	if (gameState == 1)
	{
		ball.Draw(gfx);
	}
	else if (gameState == 4)
	{
		SpriteCodex::DrawYouWin(250, 225, gfx);
	}
	else if (gameState == 2)
	{
		SpriteCodex::DrawYouLose(250, 225, gfx);
	}
	else if (gameState == 3)
	{
		SpriteCodex::DrawReady(Graphics::GetScreenRect().GetCenter(), gfx);
	}
}
