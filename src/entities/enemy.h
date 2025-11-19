#pragma once

#include "../utilities.h"

#include "raylib.h"

const int maxEnemys = 5;

namespace flappy
{
	struct Enemy
	{
		Rectangle enemyFigureDown;
		Rectangle enemyFigureUp;
		float speed;

		bool isAlive;
		Texture2D pipesTextUp;
		Texture2D pipesTextDown;
		bool scored1;
		bool scored2;
	};

	extern Enemy enemy[maxEnemys];
	void InitEnemy();
	void CreateEnemy();
	void UpdateEnemy();
	void DrawEnemy();
	void CheckPlayerColision(Rectangle playerHitBox, bool& isHit);
}