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
		player.rotation = 0.0f;
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

		
		float rotMaxUp = -20.0f;
		float rotMaxDown = 60.0f;

		
		float fallRotSpeed = 80.0f; // 

		player.speed += gravity * GetFrameTime();

		// salto
		if (player.moveUp)
		{
			player.speed = jumpForce;
			player.moveUp = false;

		
			player.rotation = rotMaxUp;
		}
		else
		{
			
			if (player.speed > 0)
				player.rotation += fallRotSpeed * GetFrameTime();
		}


		if (player.rotation > rotMaxDown)
			player.rotation = rotMaxDown;
		if (player.rotation < rotMaxUp)
			player.rotation = rotMaxUp;

		player.playerFigure.y += player.speed * GetFrameTime();

		CheckArenaCollision(player);

		player.playerHitbox.x = player.playerFigure.x + 5;
		player.playerHitbox.y = player.playerFigure.y + 5;

	}
	void DrawPlayer(Player player)
	{

		if (!player.isAlive)
			return;

		Rectangle sourceRec = { 0.0f, 0.0f, (float)player.playerText.width, (float)player.playerText.height };

		
		Rectangle destRec =
		{
			player.playerFigure.x + player.playerFigure.width / 2.0f, 
			player.playerFigure.y + player.playerFigure.height / 2.0f,
			(float)player.playerText.width,
			(float)player.playerText.height
		};

		// origen de rotación: centro de la textura
		Vector2 origin = { player.playerText.width / 2.0f, player.playerText.height / 2.0f };

		DrawTexturePro(player.playerText, sourceRec, destRec, origin, player.rotation, WHITE);

	}

	void DrawPlayer2(Player player)
	{
		if (!player.isAlive)
			return;

		Rectangle sourceRec = { 0.0f, 0.0f, (float)player.playerText.width, (float)player.playerText.height };

	
		Rectangle destRec =
		{
			player.playerFigure.x + player.playerFigure.width / 2.0f, 
			player.playerFigure.y + player.playerFigure.height / 2.0f, 
			(float)player.playerText.width,
			(float)player.playerText.height
		};

	
		Vector2 origin = { player.playerText.width / 2.0f, player.playerText.height / 2.0f };

		DrawTexturePro(player.player2Text, sourceRec, destRec, origin, player.rotation, WHITE);
	}

	void CheckArenaCollision(Player& player)
	{
		
		if (player.playerFigure.y < 0.0f)
		{
			player.playerFigure.y = 0.0f;
			player.speed = 0.0f; 
		}

		if (player.playerFigure.y + player.playerFigure.height > GetScreenHeight())
		{
			player.playerFigure.y = GetScreenHeight() - player.playerFigure.height;
			player.speed = 0.0f;
			player.isAlive = false;      
			player.playerGotHit = true;  
		}
	}
}