#include "score.h"
#include "entities/enemy.h"
#include "entities/player.h"
#include "audio.h"

namespace flappy
{
	int score1 = 0;
	int score2 = 0;
	Texture2D scoreText;

	void InitScore()
	{
		scoreText = LoadTexture("res/score.png");
	}

	void UpdateScore1(Player& player)
	{
		for (int i = 0; i < maxEnemys; i++)
		{
			if (!enemy[i].isAlive) continue;

			float pipeRight = enemy[i].enemyFigureDown.x + enemy[i].enemyFigureDown.width;
			float playerX = player.playerFigure.x;

			if (!enemy[i].scored1 && playerX > pipeRight)
			{
				PlaySound(scoreSound);
				score1++;
				enemy[i].scored1 = true;
			}
		}
	}

	void UpdateScore2(Player& player)
	{
		for (int i = 0; i < maxEnemys; i++)
		{
			if (!enemy[i].isAlive) continue;

			float pipeRight = enemy[i].enemyFigureDown.x + enemy[i].enemyFigureDown.width;
			float playerX = player.playerFigure.x;

			if (!enemy[i].scored2 && playerX > pipeRight)
			{
				PlaySound(scoreSound);
				score2++;
				enemy[i].scored2 = true;
			}
		}
	}

	void ResetScore()
	{
		score1 = 0;
		score2 = 0;
		for (int i = 0; i < maxEnemys; i++)
		{
			enemy[i].scored1 = false;
			enemy[i].scored2 = false;
		}
	}

	void DrawScore()
	{

		DrawTexture(scoreText, 10, 10, WHITE);
		DrawTextEx(paperFont, TextFormat("%i", score1), { 150, 20 }, 40, 1, BLACK);
	
	}
	void DrawScore2()
	{
		DrawTexture(scoreText, 800, 10, WHITE);
		DrawTextEx(paperFont, TextFormat("%i", score2), { 940, 20 }, 40, 1, BLACK);
	}
}
