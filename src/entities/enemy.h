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
		Texture2D pipesTextUp;
		Texture2D pipesTextDown;
	};

	void InitEnemy();
	void CreateEnemy();
	void UpdateEnemy();
	void DrawEnemy();
	void CheckPlayerColision(Rectangle playerHitBox, bool& isHit);
}