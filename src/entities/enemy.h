#pragma once

#include "../utilities.h"

#include "raylib.h"

namespace flappy
{
	struct Enemy
	{
		Rectangle enemyFigureDown;
		Rectangle enemyFigureUp;
		float speed;

		bool isAlive;
	};

	void InitEnemy();
	void CreateEnemy();
	void UpdateEnemy();
	void DrawEnemy();
	void CheckPlayerColision(Circle playerHitBox, bool& isHit);
}