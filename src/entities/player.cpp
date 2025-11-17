#include "player.h"

namespace flappy
{
	void CheckArenaCollision(Player& player);

	void InitPlayer(Player& player)

	{
		player.playerText = LoadTexture("res/fish.png");
		player.player2Text = LoadTexture("res/fish2.png");
		player.playerFigure.x = 200.0f;
		player.playerFigure.y = 300.0f;
		player.playerFigure.width = 30.0f;
		player.playerFigure.height = 40.0f;
	
		player.playerHitbox.x = player.playerFigure.x + 5;  
		player.playerHitbox.y = player.playerFigure.y + 5;
		player.playerHitbox.width = player.playerFigure.width - 10;
		player.playerHitbox.height = player.playerFigure.height - 10;

		player.lives = 1;
		player.speed = 300.0f;

		player.moveUp = false;
		player.playerGotHit = false;
		player.isAlive = true;
	}
	void InputPlayer(Player& player)
	{
		player.moveUp = IsKeyPressed(KEY_W);
	}

	void InputPlayer2(Player& player)
	{
		player.moveUp = IsKeyPressed(KEY_UP);

	}

	void UpdatePlayer(Player& player)
	{

		float gravity = 1000.0f;   
		float jumpForce = -450.0f; 

	
		player.speed += gravity * GetFrameTime();

		// salto
		if (player.moveUp)
		{
			player.speed = jumpForce;
			player.moveUp = false; 
		}

		player.playerFigure.y += player.speed * GetFrameTime();

		CheckArenaCollision(player);

		player.playerHitbox.x = player.playerFigure.x + 5;
		player.playerHitbox.y = player.playerFigure.y + 5;

	}
	void DrawPlayer(Player player)
	{

		if (!player.isAlive)
			return;

		DrawTexture(player.playerText, (int)player.playerFigure.x, (int)player.playerFigure.y, WHITE);

	}

	void DrawPlayer2(Player player)
	{
		if (!player.isAlive)
			return;

		DrawTexture(player.player2Text, (int)player.playerFigure.x, (int)player.playerFigure.y, WHITE);
	}

	void CheckArenaCollision(Player& player)
	{
		// límite superior
		if (player.playerFigure.y < 0.0f)
		{
			player.playerFigure.y = 0.0f;
			player.speed = 0.0f; // detener impulso hacia arriba
		}

		// límite inferior: perder si toca
		if (player.playerFigure.y + player.playerFigure.height > GetScreenHeight())
		{
			player.playerFigure.y = GetScreenHeight() - player.playerFigure.height;
			player.speed = 0.0f;
			player.isAlive = false;      // marcar jugador como muerto
			player.playerGotHit = true;  // opcional, para efectos de golpe
		}
	}
}