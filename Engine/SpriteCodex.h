#pragma once

#include "Graphics.h"
#include "Vec2.h"

class SpriteCodex
{
public:
	// centered drawing of 14x14 sprite
	static void DrawBall( const Vec2& center,Graphics& gfx );
	// 300px by 150px
	static void DrawTitle(const int x,const int y, Graphics& gfx);
	static void DrawStartMessage(const int x, const int y, Graphics& gfx);
};