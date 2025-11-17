#pragma once

#include "../utilities.h"

#include "raylib.h"

namespace flappy
{
	struct Player
	{
		Rectangle playerFigure;
		Rectangle playerHitbox;
		int lives;
		float speed;

		bool moveUp;
		bool playerGotHit;
		bool isAlive;
		Texture2D playerText;
		Texture2D player2Text;
	};

	void InitPlayer(Player& player);
	void InputPlayer(Player& player);
	void InputPlayer2(Player& player);
	void UpdatePlayer(Player& player);
	void DrawPlayer(Player player);
	void DrawPlayer2(Player player);
}