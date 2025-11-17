#include "enemy.h"


namespace flappy
{
	const int maxEnemys = 5;

	float spawnTimer = 0.0f;
	float spawnDelay = 2.0f;
	float enemyCounter = 0;

	Enemy enemy[maxEnemys];

	void CheckArenaLimits(int i);

	void InitEnemy()
	{
		
		for (int i = 0; i < maxEnemys; i++)
		{
			enemy[i].pipesTextUp = LoadTexture("res/pipe.png");
			enemy[i].pipesTextDown = LoadTexture("res/pipeDown.png");

			enemy[i].enemyFigureUp = { 0, 0,
				(float)enemy[i].pipesTextUp.width,
				(float)enemy[i].pipesTextUp.height
			};

			enemy[i].enemyFigureDown = { 0, 0,
				(float)enemy[i].pipesTextDown.width,
				(float)enemy[i].pipesTextDown.height
			};

			enemy[i].speed = 200.0f;
			enemy[i].isAlive = false;
		}
	}

	void CreateEnemy()
	{
		float gap = 230.0f;
		int minY = 100;
		int maxY = 350;

		for (int i = 0; i < maxEnemys; i++)
		{
			if (!enemy[i].isAlive)
			{
				float topHeight = (float)GetRandomValue(minY, maxY);

				float startX = (float)GetScreenWidth() + 200;

				// tubo arriba
				enemy[i].enemyFigureUp.x = startX;
				enemy[i].enemyFigureUp.y = topHeight - enemy[i].enemyFigureUp.height;

				// tubo abajo
				enemy[i].enemyFigureDown.x = startX;
				enemy[i].enemyFigureDown.y = topHeight + gap;

				enemy[i].isAlive = true;
				break;
			}
		}
	}
	void UpdateEnemy()
	{
		spawnTimer += GetFrameTime();

		if (spawnTimer >= spawnDelay && enemyCounter < maxEnemys)
		{
			CreateEnemy();
			spawnTimer = 0;
		}

		for (int i = 0; i < maxEnemys; i++)
		{
			if (enemy[i].isAlive)
			{
				enemy[i].enemyFigureDown.x -= enemy[i].speed * GetFrameTime();
				enemy[i].enemyFigureUp.x = enemy[i].enemyFigureDown.x;
				CheckArenaLimits(i);
			}
		}
	}
	void DrawEnemy()
	{
		for (int i = 0; i < maxEnemys; i++)
		{
			if (enemy[i].isAlive)
			{
				DrawTexture(enemy[i].pipesTextUp, (int)enemy[i].enemyFigureUp.x, (int)enemy[i].enemyFigureUp.y, WHITE);
		
				DrawTexture(enemy[i].pipesTextDown, (int)enemy[i].enemyFigureDown.x, (int)enemy[i].enemyFigureDown.y, WHITE);
			}
		}
	}

	void CheckArenaLimits(int i)
	{
		if (enemy[i].isAlive && enemy[i].enemyFigureDown.x < 0.0f - enemy[i].enemyFigureDown.width)
		{
			enemy[i].isAlive = false;
		}
	}

	void CheckPlayerColision(Rectangle playerHitBox, bool& isHit)
	{
		for (int i = 0; i < maxEnemys; i++)
		{
			if (enemy[i].isAlive)
			{
				// colisión con el tubo de abajo
				if (playerHitBox.x < enemy[i].enemyFigureDown.x + enemy[i].enemyFigureDown.width &&
					playerHitBox.x + playerHitBox.width > enemy[i].enemyFigureDown.x &&
					playerHitBox.y < enemy[i].enemyFigureDown.y + enemy[i].enemyFigureDown.height &&
					playerHitBox.y + playerHitBox.height > enemy[i].enemyFigureDown.y)
				{
					isHit = true;
				}

				// colisión con el tubo de arriba
				else if (playerHitBox.x < enemy[i].enemyFigureUp.x + enemy[i].enemyFigureUp.width &&
					playerHitBox.x + playerHitBox.width > enemy[i].enemyFigureUp.x &&
					playerHitBox.y < enemy[i].enemyFigureUp.y + enemy[i].enemyFigureUp.height &&
					playerHitBox.y + playerHitBox.height > enemy[i].enemyFigureUp.y)
				{
					isHit = true;
				}
			}
		}
	}

}