#include "background.h"
 
//credits https://free-game-assets.itch.io/free-ancient-temple-pixel-game-backgrounds

namespace flappy
{
	BackGround gameBackGround;

	void InitBackGorund()
	{
		gameBackGround.part1 = LoadTexture("res/Background/Plan 1.png");
		gameBackGround.part2 = LoadTexture("res/Background/Plan 2.png");
		gameBackGround.part3 = LoadTexture("res/Background/Plan 3.png");
		gameBackGround.part4 = LoadTexture("res/Background/Plan 4.png");
		gameBackGround.part5 = LoadTexture("res/Background/Plan 5.png");

		gameBackGround.scrollPart1 = 0.0f;
		gameBackGround.scrollPart2 = 0.0f;
		gameBackGround.scrollPart3 = 0.0f;
		gameBackGround.scrollPart4 = 0.0f;
		gameBackGround.scrollPart5 = 0.0f;
	}
	void UpdateBackGorund()
	{
		gameBackGround.scrollPart1 -= 160.0f * GetFrameTime();
		gameBackGround.scrollPart2 -= 150.0f * GetFrameTime();
		gameBackGround.scrollPart3 -= 130.0f * GetFrameTime();
		gameBackGround.scrollPart4 -= 110.0f * GetFrameTime();
		gameBackGround.scrollPart5 -= 90.0f * GetFrameTime();

		if (gameBackGround.scrollPart1 <= -gameBackGround.part1.width * 2)
			gameBackGround.scrollPart1 = 0;

		if (gameBackGround.scrollPart2 <= -gameBackGround.part2.width * 2)
			gameBackGround.scrollPart2 = 0;

		if (gameBackGround.scrollPart3 <= -gameBackGround.part3.width * 2)
			gameBackGround.scrollPart3 = 0;

		if (gameBackGround.scrollPart4 <= -gameBackGround.part4.width * 2)
			gameBackGround.scrollPart4 = 0;

		if (gameBackGround.scrollPart5 <= -gameBackGround.part5.width * 2)
			gameBackGround.scrollPart5 = 0;
	}
	void DrawBackGround()
	{
		Color backColor = WHITE;

		DrawTextureEx(gameBackGround.part5, { gameBackGround.scrollPart5 ,0.0f }, 0.0f, 3.0f, backColor);
		DrawTextureEx(gameBackGround.part5, { gameBackGround.part5.width*2 + gameBackGround.scrollPart5 ,0.0f }, 0.0f, 3.0f, backColor);

		DrawTextureEx(gameBackGround.part4, { gameBackGround.scrollPart4 ,0.0f }, 0.0f, 3.0f, backColor);
		DrawTextureEx(gameBackGround.part4, { gameBackGround.part4.width*2 + gameBackGround.scrollPart4 ,0.0f }, 0.0f, 3.0f, backColor);

		DrawTextureEx(gameBackGround.part3, { gameBackGround.scrollPart3 ,120.0f }, 0.0f, 2.0f, backColor);
		DrawTextureEx(gameBackGround.part3, { gameBackGround.part3.width*2 + gameBackGround.scrollPart3 ,120.0f }, 0.0f, 2.0f, backColor);

		DrawTextureEx(gameBackGround.part2, { gameBackGround.scrollPart2 ,120.0f }, 0.0f, 2.0f, backColor);
		DrawTextureEx(gameBackGround.part2, { gameBackGround.part2.width*2 + gameBackGround.scrollPart2 ,120.0f }, 0.0f, 2.0f, backColor);

		DrawTextureEx(gameBackGround.part1, { gameBackGround.scrollPart1 ,54.0f }, 0.0f, 2.0f, backColor);
		DrawTextureEx(gameBackGround.part1, { gameBackGround.part1.width*2 + gameBackGround.scrollPart1 ,54.0f }, 0.0f, 2.0f, backColor);
	}

	void UnloadBackGorund()
	{
		UnloadTexture(gameBackGround.part1);
		UnloadTexture(gameBackGround.part2);
		UnloadTexture(gameBackGround.part3);
		UnloadTexture(gameBackGround.part4);
		UnloadTexture(gameBackGround.part5);
	}
}