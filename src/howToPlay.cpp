#include "howToPlay.h"
#include "raylib.h"
#include "utilities.h"

namespace flappy
{

	Texture2D howToPlayText;
	void InitHowToPlay()
	{
		howToPlayText = LoadTexture("res/howtoplay.png");
	}

	void UpdateHowToPlay(GameStats& gameStats)
	{
		// Solo actualizar si estamos en la pantalla HowToPlay
		if (gameStats.gameStatus != SceneStatus::GAMERULES) return;

		// Si el jugador aprieta ENTER, empieza el juego
		if (IsKeyPressed(KEY_ENTER))
		{
			gameStats.gameStatus = gameStats.previousGameplayMode; 
		}
	}  

	void DrawHowToScreen()
	{
		DrawTexture(howToPlayText, 0, 0, WHITE);

		DrawTextEx(paperFont, "Press enter to play", { 690, 710 }, 40, 1, BLACK);
		
	}
}
