#include "game.h"

#include <iostream>

#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/menu.h"
#include "entities/background.h"

using namespace std;

namespace flappy
{

	Player player;
	Player player2;
	GameStats gameStats;
	MenuButtons buttons;



	void Init();
	void Input();
	void Update();
	void Draw();
	void DrawSplitScreenGameplay();

	void RunGame()
	{
		Init();

		while (!WindowShouldClose())
		{
			Input();
			Update();
			Draw();
		}

		UnloadBackGorund();
		CloseWindow();
	}

	void Init()
	{
		const int screenWidth = 1024;
		const int screenHeight = 768;

		InitWindow(screenWidth, screenHeight, "Aracnoids");

		InitBackGorund();

		InitPlayer(player);
		InitPlayer(player2);
		// Posiciones iniciales distintas
		player.playerFigure.x = 200;
		player.playerFigure.y = 300;

		player2.playerFigure.x = screenWidth / 2 + 200;
		player2.playerFigure.y = 300;

		InitEnemy(enemiesP1, MAX_ENEMIES);
		InitEnemy(enemiesP2, MAX_ENEMIES);
		InitButtons(buttons);
	}

	void Input()
	{
		switch ((SceneStatus)gameStats.gameStatus)
		{
		case SceneStatus::GAMEMENU:
			break;
		case SceneStatus::GAMERULES:
			break;
		case SceneStatus::GAMECREDITS:
			break;
		case SceneStatus::FIRSTGAME:
			break;
		case SceneStatus::GAMEPLAY:
			InputPlayer(player);
			break;
		case SceneStatus::GAMEPLAY2P:
			InputPlayer(player);  // Jugador 1
			InputPlayer2(player2);
			break;
		case SceneStatus::GAMEPAUSE:
			break;
		case SceneStatus::RESETGAME:
			break;
		case SceneStatus::GAMEEND:
			break;

		default:
			break;
		}
	}

	void Update()
	{
		switch ((SceneStatus)gameStats.gameStatus)
		{
		case SceneStatus::GAMEMENU:
			UpdateSceneMenus(gameStats, buttons);
			break;
		case SceneStatus::GAMERULES:
			UpdateSceneMenus(gameStats, buttons);
			break;
		case SceneStatus::GAMECREDITS:
			UpdateSceneMenus(gameStats, buttons);

			break;
		case SceneStatus::FIRSTGAME:

			UpdateSceneMenus(gameStats, buttons);

			break;
		case SceneStatus::GAMEPLAY:

			UpdateBackGorund();
			UpdatePlayer(player);
			UpdateEnemy(enemiesP1, MAX_ENEMIES, spawnTimerP1, true, false);
			CheckPlayerCollision(enemiesP1, MAX_ENEMIES, player.playerHitbox, player.playerGotHit);

			UpdateSceneMenus(gameStats, buttons);

			if (player.playerGotHit)
			{
				gameStats.gameStatus = SceneStatus::RESETGAME;
			}
			break;

		case SceneStatus::GAMEPLAY2P:
			UpdateBackGorund();

			// Ambos jugadores
			UpdatePlayer(player);
			UpdatePlayer(player2);

			// Enemigos independientes para cada lado
			UpdateEnemy(enemiesP1, MAX_ENEMIES, spawnTimerP1, true, true);
			UpdateEnemy(enemiesP2, MAX_ENEMIES, spawnTimerP2, false, true);

			// Colisiones separadas
			CheckPlayerCollision(enemiesP1, MAX_ENEMIES, player.playerHitbox, player.playerGotHit);
			CheckPlayerCollision(enemiesP2, MAX_ENEMIES, player2.playerHitbox, player2.playerGotHit);

			UpdateSceneMenus(gameStats, buttons);

			if (player.playerGotHit || player2.playerGotHit)
			{
				gameStats.gameStatus = SceneStatus::RESETGAME;
			}
			break;
		case SceneStatus::GAMEPAUSE:

			UpdateSceneMenus(gameStats, buttons);

			break;
		case SceneStatus::RESETGAME:

			InitPlayer(player);
			InitPlayer(player2);
			InitEnemy(enemiesP1, MAX_ENEMIES);
			InitEnemy(enemiesP2, MAX_ENEMIES);
			spawnTimerP1 = 0.0f;
			spawnTimerP2 = 0.0f;
			gameStats.gameStatus = SceneStatus::FIRSTGAME;
			break;
		case SceneStatus::GAMEEND:

			UpdateSceneMenus(gameStats, buttons);

			break;

		default:
			break;
		}
	}

	void Draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);

		switch ((SceneStatus)gameStats.gameStatus)
		{
		case SceneStatus::GAMEMENU:
			DrawMenuTypeScene(gameStats, buttons);
			break;
		case SceneStatus::GAMERULES:
			DrawMenuTypeScene(gameStats, buttons);

			break;
		case SceneStatus::GAMECREDITS:
			DrawMenuTypeScene(gameStats, buttons);

			break;
		case SceneStatus::FIRSTGAME:
			DrawBackGround();

			DrawPlayer(player);
			DrawMenuTypeScene(gameStats, buttons);

			break;
		case SceneStatus::GAMEPLAY:

			DrawBackGround();
			DrawPlayer(player);
			DrawEnemy(enemiesP1, MAX_ENEMIES);

			break;
		case SceneStatus::GAMEPLAY2P:
			DrawSplitScreenGameplay();
			break;
		case SceneStatus::GAMEPAUSE:
			DrawBackGround();
			DrawPlayer(player);
			DrawEnemy(enemiesP1, MAX_ENEMIES);

			DrawEnemy(enemiesP2, MAX_ENEMIES);

			DrawMenuTypeScene(gameStats, buttons);

			break;
		case SceneStatus::RESETGAME:
			/*DrawText("colision",static_cast <int> (player.playerFigure.x),
				static_cast <int> (player.playerFigure.y - player.playerFigure.height/2), auxFont, WHITE);*/
			break;
		case SceneStatus::GAMEEND:
			DrawBackGround();

			
			DrawPlayer(player);
			DrawEnemy(enemiesP1, MAX_ENEMIES);

			
			DrawPlayer(player2);
			DrawEnemy(enemiesP2, MAX_ENEMIES);

			DrawMenuTypeScene(gameStats, buttons);

			break;

		default:
			break;
		}



		EndDrawing();
	}

	void DrawSplitScreenGameplay()
	{
		int screenWidth = GetScreenWidth();
		int screenHeight = GetScreenHeight();

		// Mitad izquierda (Jugador 1)
		BeginScissorMode(0, 0, screenWidth / 2, screenHeight);
		DrawBackGround();
		DrawPlayer(player);
		DrawEnemy(enemiesP1, MAX_ENEMIES);
		DrawText("Jugador 1", 40, 20, 20, WHITE);
		EndScissorMode();

		// Mitad derecha (Jugador 2)
		BeginScissorMode(screenWidth / 2, 0, screenWidth / 2, screenHeight);
		DrawBackGround();
		DrawPlayer(player2);
		DrawEnemy(enemiesP2, MAX_ENEMIES);
		DrawText("Jugador 2", screenWidth / 2 + 40, 20, 20, WHITE);
		EndScissorMode();

		DrawRectangle(screenWidth / 2 - 2, 0, 4, screenHeight, GRAY);
	}

}