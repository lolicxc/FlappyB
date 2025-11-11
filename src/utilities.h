#pragma once

#include "raylib.h"

namespace flappy
{
	struct Circle
	{
		Vector2 pos;
		float rad;
	};

	enum class SceneStatus
	{
		GAMEMENU = 1,
		GAMERULES,
		GAMECREDITS,
		FIRSTGAME,
		GAMEPLAY,
		GAMEPLAY2P,
		GAMEPAUSE,
		RESETGAME,
		GAMEEND,
		SIMEND
	};

	struct GameStats
	{
		SceneStatus gameStatus = SceneStatus::GAMEMENU;

		int fontSize = 25;
	};
}
