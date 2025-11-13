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
			enemy[i].enemyFigureDown.x = 0.0f;
			enemy[i].enemyFigureDown.y = 0.0f;
			enemy[i].enemyFigureDown.width = 50.0f;
			enemy[i].enemyFigureDown.height = 600.0f;

			enemy[i].enemyFigureUp.x = 0.0f;
			enemy[i].enemyFigureUp.y = 0.0f;
			enemy[i].enemyFigureUp.width = 50.0f;
			enemy[i].enemyFigureUp.height = 600.0f;

			enemy[i].isAlive = false;
			enemy[i].speed = 200.0f;
		}
	}

	void CreateEnemy()
	{
		float auxPosX = 50.0f;
		int minRangeYPos = 200;
		int maxRangeYPos = 700;
		int minEmptySpace = 170;

		for (int i = 0; i < maxEnemys; i++)
		{
			if (!enemy[i].isAlive)
			{
				enemy[i].enemyFigureDown.x = GetScreenWidth() + auxPosX;
				enemy[i].enemyFigureDown.y = static_cast<float>(GetRandomValue(minRangeYPos, maxRangeYPos));

				enemy[i].enemyFigureUp.x = enemy[i].enemyFigureDown.x;
				enemy[i].enemyFigureUp.y = (enemy[i].enemyFigureDown.y - enemy[i].enemyFigureUp.height - minEmptySpace);

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
				DrawRectangle(static_cast <int>(enemy[i].enemyFigureDown.x),
					static_cast <int>(enemy[i].enemyFigureDown.y),
					static_cast <int>(enemy[i].enemyFigureDown.width),
					static_cast <int>(enemy[i].enemyFigureDown.height), RED);

				DrawRectangle(static_cast <int>(enemy[i].enemyFigureUp.x),
					static_cast <int>(enemy[i].enemyFigureUp.y),
					static_cast <int>(enemy[i].enemyFigureUp.width),
					static_cast <int>(enemy[i].enemyFigureUp.height), RED);
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

	void CheckPlayerColision(Circle playerHitBox, bool& isHit)
	{
		for (int i = 0; i < maxEnemys; i++)
		{
			if (enemy[i].isAlive
				&& playerHitBox.pos.x + playerHitBox.rad >= enemy[i].enemyFigureDown.x
				&& playerHitBox.pos.y + playerHitBox.rad >= enemy[i].enemyFigureDown.y
				&& playerHitBox.pos.x - playerHitBox.rad <= enemy[i].enemyFigureDown.x + enemy[i].enemyFigureDown.width)
			{
				isHit = true;
			}

			else if (enemy[i].isAlive
				&& playerHitBox.pos.x + playerHitBox.rad >= enemy[i].enemyFigureUp.x
				&& playerHitBox.pos.y + playerHitBox.rad <= enemy[i].enemyFigureUp.y + enemy[i].enemyFigureUp.height
				&& playerHitBox.pos.x - playerHitBox.rad <= enemy[i].enemyFigureUp.x + enemy[i].enemyFigureUp.width)
			{
				isHit = true;
			}
		}
	}
}