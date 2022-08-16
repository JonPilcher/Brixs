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
	ball(Vec2(300.0f, 300.0f), Vec2(300.f, 300.0f)),
	walls(0.0f, float(gfx.ScreenWidth), 0.0f, float(gfx.ScreenHeight)),
	soundPad(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\arkbrick.wav"),
	soundTitle(L"Sounds\\title.wav"),
	soundYouWin(L"Sounds\\YouWin.wav"),
	soundYouLose(L"Sounds\\YouLose.wav"),
	soundMissedBall(L"Sounds\\missedBall.wav"),
	paddle(Vec2(500.0f, 500.0f), 50.0f, 10.0f)
{
	const Vec2 topLeft(40.0f, 40.0f);
	int i = 0;
	for (int y = 0; y < nBricksDown; ++y)
	{
		const Color c = brickColor[y];
		for (int x = 0; x < nBricksAcross; ++x)
		{
			brick[i] = Brick(Rectf(topLeft + Vec2(x * brickWidth,y * brickHeight),brickWidth,brickHeight),c);
			++i;
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
	if (isGameStarted)
	{
		if (!gameOver)
		{
			
			if (!ball.IsGameOver())
			{
				paddle.Update(wnd.kbd, dt);
				paddle.DoWallCollision(walls);
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
					gameOver = true;
					soundYouWin.Play();
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
				if (ball.DoWallCollision(walls))
				{
					paddle.ResetCoolDown();
					soundPad.Play();
				}
				if (ball.IsGameOver())
				{
					soundYouLose.Play();
				}
				if (ball.missedBall)
				{
					soundMissedBall.Play();
				paddle.ResetCoolDown();
				}
				ball.missedBall = false;
				
			}
		}
	}
	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		isGameStarted = true;
	}
}

void Game::ComposeFrame()
{
	if (!isGameStarted)
	{
		SpriteCodex::DrawTitle(250, 150, gfx);
		SpriteCodex::DrawStartMessage(250, 300, gfx);
	}
	else if(!gameOver || !ball.IsGameOver())
	{
		SpriteCodex::DrawWalls(0, 0, gfx);
		SpriteCodex::DrawWalls(759, 0, gfx);
		SpriteCodex::DrawTop(40, 0, gfx);
		ball.Draw(gfx);
		for (const Brick& b : brick)
		{
			b.Draw(gfx);
		}
		paddle.Draw(gfx);
	}
	if (gameOver)
	{
		SpriteCodex::DrawYouWin(250, 225, gfx);
	}
	if (ball.IsGameOver())
	{
		SpriteCodex::DrawYouLose(250, 225, gfx);
	}
}
