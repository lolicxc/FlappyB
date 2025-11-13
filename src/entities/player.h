#pragma once

#include "../utilities.h"

#include "raylib.h"

namespace flappy
{
	struct Player
	{
		Rectangle playerFigure;
		Circle playerHitbox;
		int lives;
		float speed;

		bool moveUp;
		bool playerGotHit;
		bool isAlive;
	};

	void InitPlayer(Player& player);
	void InputPlayer(Player& player);
	void InputPlayer2(Player& player);
	void UpdatePlayer(Player& player);
	void DrawPlayer(Player player);
}