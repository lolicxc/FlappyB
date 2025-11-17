#pragma once

#include "raylib.h" 

namespace flappy
{
	struct BackGround
	{
		
		Texture2D  part2;
		Texture2D  part3;
		Texture2D  part4;
		Texture2D  part5;

		float scrollPart1;
		float scrollPart2;
		float scrollPart3;
		float scrollPart4;
		float scrollPart5;
	};

	void InitBackGorund();
	void UpdateBackGorund();
	void DrawBackGround();
	void UnloadBackGorund();
}