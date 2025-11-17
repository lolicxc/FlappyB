#include "background.h"
 


namespace flappy
{
	BackGround gameBackGround;

	void InitBackGorund()
	{
		
		gameBackGround.part2 = LoadTexture("res/Background/Plan 2.png");
		gameBackGround.part3 = LoadTexture("res/Background/Plan 3.png");
		gameBackGround.part4 = LoadTexture("res/Background/Plan 4.png");
		gameBackGround.part5 = LoadTexture("res/Background/Plan 5.png");

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

		if (gameBackGround.scrollPart2 <= -gameBackGround.part2.width)
			gameBackGround.scrollPart2 = 0;

		if (gameBackGround.scrollPart3 <= -gameBackGround.part3.width)
			gameBackGround.scrollPart3 = 0;

		if (gameBackGround.scrollPart4 <= -gameBackGround.part4.width)
			gameBackGround.scrollPart4 = 0;

		if (gameBackGround.scrollPart5 <= -gameBackGround.part5.width)
			gameBackGround.scrollPart5 = 0;
	}

	void DrawBackGround()
	{
		Color backColor = WHITE;

		int w5 = gameBackGround.part5.width;
		DrawTexture(gameBackGround.part5, (int)gameBackGround.scrollPart5, 0, backColor);
		DrawTexture(gameBackGround.part5, (int)(gameBackGround.scrollPart5 + w5), 0, backColor);

		// --- Capa 4 ---
		int w4 = gameBackGround.part4.width;
		DrawTexture(gameBackGround.part4, (int)gameBackGround.scrollPart4, 200, backColor);
		DrawTexture(gameBackGround.part4, (int)(gameBackGround.scrollPart4 + w4), 200, backColor);

		// --- Capa 3 ---
		int w3 = gameBackGround.part3.width;
		DrawTexture(gameBackGround.part3, (int)gameBackGround.scrollPart3, 380, backColor);
		DrawTexture(gameBackGround.part3, (int)(gameBackGround.scrollPart3 + w3), 380, backColor);

		// --- Piso ---
		int w2 = gameBackGround.part2.width;
		int h2 = gameBackGround.part2.height;

		int floorYf = GetScreenHeight() - h2;
		int floorY = (int)floorYf;

		DrawTexture(gameBackGround.part2, (int)gameBackGround.scrollPart2, floorY, backColor);
		DrawTexture(gameBackGround.part2, (int)(gameBackGround.scrollPart2 + w2), floorY, backColor);

	}



	void UnloadBackGorund()
	{
		 
		UnloadTexture(gameBackGround.part2);
		UnloadTexture(gameBackGround.part3);
		UnloadTexture(gameBackGround.part4);
		UnloadTexture(gameBackGround.part5);
	}
}