#include "player.h"
#include "../Audio.h"
namespace flappy
{
	void CheckArenaCollision(Player& player);

	void InitPlayer(Player& player)

	{
		player.playerText = LoadTexture("res/fish.png");
		player.player2Text = LoadTexture("res/fish2.png");
		player.hitTextP1 = LoadTexture("res/deadAnim.png");
		player.hitTextP2 = LoadTexture("res/deadAnim2.png");
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

		player.hitMaxFrames = 4;
		player.hitCurrentFrame = 0;
		player.hitTimer = 0.0f;
		player.hitFrameTime = 0.1f;

		player.deathTimer = 0.0f;      
		player.deathDuration = 1.0f;
		player.finishedDeathAnim = false;

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
		float fallRotSpeed = 80.0f;

		if (!player.playerGotHit && !player.finishedDeathAnim) 
		{
			player.speed += gravity * GetFrameTime();

			if (player.moveUp)
			{
				PlaySound(jumpSound);
				player.speed = jumpForce;
				player.moveUp = false;
				player.rotation = rotMaxUp;
			}
			else if (player.speed > 0)
				player.rotation += fallRotSpeed * GetFrameTime();

			if (player.rotation > rotMaxDown) player.rotation = rotMaxDown;
			if (player.rotation < rotMaxUp) player.rotation = rotMaxUp;

			player.playerFigure.y += player.speed * GetFrameTime();
			CheckArenaCollision(player);

			player.playerHitbox.x = player.playerFigure.x + 5;
			player.playerHitbox.y = player.playerFigure.y + 5;
		}
		else
		{
		
			player.hitTimer += GetFrameTime();

			if (player.hitTimer >= player.hitFrameTime)
			{
				player.hitTimer = 0;
				if (player.hitCurrentFrame < player.hitMaxFrames - 1)
				{
					player.hitCurrentFrame++;
				}
				else
				{
					
					player.finishedDeathAnim = true;
				}

			}
		}
	}

	void DrawPlayer(Player player)
	{

		if (!player.isAlive && player.finishedDeathAnim)
			return;

			int frameWidth = player.hitTextP1.width / player.hitMaxFrames;

			int frame = player.playerGotHit ? player.hitCurrentFrame : 0;

			Rectangle source = {
				(float)(frame * frameWidth), 0,
				(float)frameWidth,
				(float)player.hitTextP1.height
			};

			Rectangle dest = {
				player.playerFigure.x + player.playerFigure.width / 2.0f,
				player.playerFigure.y + player.playerFigure.height / 2.0f,
				(float)frameWidth,
				(float)player.hitTextP1.height
			};

			Vector2 origin = { frameWidth / 2.0f, player.hitTextP1.height / 2.0f };

			DrawTexturePro(player.hitTextP1, source, dest, origin, player.rotation, WHITE);
		




	}

	void DrawPlayer2(Player player)
	{
		if (!player.isAlive && player.finishedDeathAnim)
			return;

		int frameWidth = player.hitTextP2.width / player.hitMaxFrames;

		int frame = player.playerGotHit ? player.hitCurrentFrame : 0;

		Rectangle source = {
			(float)(frame * frameWidth), 0,
			(float)frameWidth,
			(float)player.hitTextP2.height
		};

		Rectangle dest = {
			player.playerFigure.x + player.playerFigure.width / 2.0f,
			player.playerFigure.y + player.playerFigure.height / 2.0f,
			(float)frameWidth,
			(float)player.hitTextP2.height
		};

		Vector2 origin = { frameWidth / 2.0f, player.hitTextP2.height / 2.0f };

		DrawTexturePro(player.hitTextP2, source, dest, origin, player.rotation, WHITE);
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