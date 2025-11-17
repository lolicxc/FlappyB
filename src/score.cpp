#include "score.h"
#include "entities/enemy.h"
#include "entities/player.h"

namespace flappy
{
	int score = 0;
	Texture2D scoreText;

	void InitScore()
	{
		scoreText = LoadTexture("res/score.png");
	}

	void UpdateScore(Player& player)
	{
		for (int i = 0; i < maxEnemys; i++)
		{
			if (!enemy[i].isAlive) continue;

			float pipeRight = enemy[i].enemyFigureDown.x + enemy[i].enemyFigureDown.width;
			float playerX = player.playerFigure.x;

			if (!enemy[i].scored && playerX > pipeRight)
			{
				score++;
				enemy[i].scored = true;
			}
		}
	}

	void ResetScore()
	{
		score = 0;

		for (int i = 0; i < maxEnemys; i++)
		{
			enemy[i].scored = false;
		}
	}

	int GetScore()
	{
		return score;
	}
	void DrawScore()
	{

		DrawTexture(scoreText, 10, 10, WHITE);
		DrawText(TextFormat("%i", score), 150, 20, 40, BLACK);
	}
}
