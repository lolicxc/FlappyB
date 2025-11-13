#include "player.h"

namespace flappy
{
	void CheckArenaCollision(Player& player);

	void InitPlayer(Player& player)

	{
		player.playerFigure.x = 200.0f;
		player.playerFigure.y = 300.0f;
		player.playerFigure.width = 30.0f;
		player.playerFigure.height = 40.0f;

		player.playerHitbox.rad = 25.0f;
		player.playerHitbox.pos.x = 200.0f + player.playerFigure.width/2;
		player.playerHitbox.pos.y = 300.0f + player.playerFigure.height/2;

		player.lives = 1;
		player.speed = 300.0f;

		player.moveUp = false;
		player.playerGotHit = false;
		player.isAlive = true;
	}
	void InputPlayer(Player& player)
	{
		if (IsKeyDown(KEY_W))
		{
			player.moveUp = true;
		}

		if (!IsKeyDown(KEY_W))
		{
			player.moveUp = false;
		}
	}

	void InputPlayer2(Player& player)
	{
		if (IsKeyDown(KEY_UP))
		{
			player.moveUp = true;
		}

		if (!IsKeyDown(KEY_UP))
		{
			player.moveUp = false;
		}
	}

	void UpdatePlayer(Player& player)
	{

		float gravity = 1000.0f;   // fuerza de gravedad
		float jumpForce = -350.0f; // impulso hacia arriba

		// aplicar gravedad siempre
		player.speed += gravity * GetFrameTime();

		// si salta, aplicar impulso hacia arriba
		if (player.moveUp)
		{
			player.speed = jumpForce;
		}

		// actualizar posición según velocidad
		player.playerFigure.y += player.speed * GetFrameTime();

		// mantener hitbox alineado
		player.playerHitbox.pos.y = player.playerFigure.y;
	}
	void DrawPlayer(Player player)
	{
		DrawRectangle(static_cast <int>(player.playerFigure.x),
			static_cast <int>(player.playerFigure.y),
			static_cast <int>(player.playerFigure.width),
			static_cast <int>(player.playerFigure.height), RED);
		DrawCircleLines(static_cast <int>(player.playerHitbox.pos.x),
			static_cast <int>(player.playerHitbox.pos.y),
			static_cast <float>(player.playerHitbox.rad), RED);
	}

	void CheckArenaCollision(Player& player)
	{
		if (player.playerFigure.y <= 0.0f)
		{
			player.playerFigure.y += player.playerFigure.height;
		}
		if (player.playerFigure.y + player.playerFigure.height >= GetScreenHeight())
		{
			player.playerGotHit = true;
		}
	}
}