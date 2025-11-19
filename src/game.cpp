#include "game.h"

#include <iostream>

#include "entities/player.h"
#include "entities/enemy.h"
#include "entities/menu.h"
#include "entities/background.h"
#include "score.h"
#include "gameOverScreen.h"
#include "creditsScreen.h"
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


		InitWindow(screenWidth, screenHeight, "Swimmy");
		// Ahora sí cargamos la fuente
		flappy::paperFont = LoadFontEx("res/Collage.ttf", gameStats.fontSize, 0, 0);


		InitBackGorund();

		InitPlayer(player);
		InitPlayer(player2);
		InitEnemy();
		InitButtons(buttons);
		InitScore();
		InitCredits();
		InitGameOverScreen();
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
			InputPlayer(player);
			InputPlayer2(player2);
			break;
		case SceneStatus::GAMEPAUSE:
			break;
		case SceneStatus::RESETGAME:
			break;
		case SceneStatus::GAMEEND:
			break;
		case SceneStatus::GAMEOVER1:
			break;
		case SceneStatus::GAMEOVER2:
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
			ResetScore();
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
			UpdateScore1(player);
			UpdatePlayer(player);
			UpdateEnemy();
			UpdateSceneMenus(gameStats, buttons);
			CheckPlayerColision(player.playerHitbox, player.playerGotHit);

			if (player.playerGotHit)
			{
				gameStats.gameStatus = SceneStatus::GAMEOVER1;
			}
			break;
		case SceneStatus::GAMEPLAY2P:
			UpdateBackGorund();
			if (player.isAlive)
			{
				UpdateScore1(player);
				UpdatePlayer(player);
				CheckPlayerColision(player.playerHitbox, player.playerGotHit);
				if (player.playerGotHit)
					player.isAlive = false;
			}

			if (player2.isAlive)
			{
				UpdateScore2(player2);
				UpdatePlayer(player2);
				CheckPlayerColision(player2.playerHitbox, player2.playerGotHit);
				if (player2.playerGotHit)
					player2.isAlive = false;
			}

			UpdateEnemy();
			UpdateSceneMenus(gameStats, buttons);

			if (!player.isAlive && !player2.isAlive)
			{
				gameStats.gameStatus = SceneStatus::GAMEOVER2;
			}
			break;
		case SceneStatus::GAMEPAUSE:

			UpdateSceneMenus(gameStats, buttons);

			break;
		case SceneStatus::RESETGAME:
			InitPlayer(player);
			InitPlayer(player2);
			player.isAlive = true;
			player2.isAlive = true;

			InitEnemy();
			gameStats.gameStatus = SceneStatus::GAMEMENU;
			break;
		case SceneStatus::GAMEEND:

			UpdateSceneMenus(gameStats, buttons);

			break;
		case SceneStatus::GAMEOVER1:

			UpdateGameOverScreen(gameStats, buttons);
			break;
		case SceneStatus::GAMEOVER2:
			UpdateGameOverScreen(gameStats, buttons);
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
			DrawEnemy();
			DrawScore();

			break;

		case SceneStatus::GAMEPLAY2P:
			DrawBackGround();
			DrawPlayer(player);
			DrawPlayer2(player2);
			DrawEnemy();
			DrawScore();
			DrawScore2();
			break;
		case SceneStatus::GAMEPAUSE:
			DrawBackGround();

			DrawPlayer(player);
			DrawEnemy();
			DrawMenuTypeScene(gameStats, buttons);

			break;
		case SceneStatus::RESETGAME:
			/*DrawText("colision",static_cast <int> (player.playerFigure.x),
				static_cast <int> (player.playerFigure.y - player.playerFigure.height/2), auxFont, WHITE);*/
			break;
		case SceneStatus::GAMEEND:
			DrawBackGround();

			DrawPlayer(player);
			DrawEnemy();
			DrawMenuTypeScene(gameStats, buttons);

			break;
		case SceneStatus::GAMEOVER1:
			DrawGameOver1P(score1, buttons);
			break;

		case SceneStatus::GAMEOVER2:
			DrawGameOver2P(score1, score2, buttons);
			break;


		default:
			break;
		}



		EndDrawing();
	}
}