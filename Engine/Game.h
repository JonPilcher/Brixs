/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Ball.h"
#include "Brick.h"
#include "FrameTimer.h"
#include "Sound.h"
#include "Paddle.h"
#include "LifeCounter.h"
#include "Walls.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel(float dt);
	/********************************/
	/*  User Functions              */
	void StartRound();
	void ResetBall();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	static constexpr float brickWidth = 40.0f;
	static constexpr float brickHeight = 22.0f;
	static constexpr int nBricksAcross = 12;
	static constexpr int nBricksDown = 4;
	static constexpr int nBricks = nBricksAcross * nBricksDown;
	static constexpr float topSpace = brickHeight * 1.6f;
	static constexpr float wallThickness = 12.0f;
	static constexpr float fieldWidth = float(nBricksAcross) * brickWidth;
	static constexpr float fieldHeight = float(Graphics::ScreenHeight -30) - wallThickness * 2.0f;
	static constexpr Color brickColors[4] = { {230,0,0},{ 0,230,0 },{ 0,0,230 },{ 0,230,230 } };
	static constexpr Color wallColor = { 20,60,200 };
	static constexpr float readyWaitTime = 4.3f;
	FrameTimer ft;
	Ball ball;
	Walls walls;
	Brick brick[nBricks];
	LifeCounter lifeCounter;
	Paddle paddle;
	Sound soundPad;
	Sound soundBrick;
	Sound soundTitle;
	Sound soundYouLose;
	Sound soundYouWin;
	Sound soundMissedBall;
	Sound soundGetReady;
	int gameState = 0;
	float curWaitTime;
	bool isGameStarted = false;
	bool gameOver = false; 
	int playSound = 0;
	/********************************/
};