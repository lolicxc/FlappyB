#pragma once
#include "utilities.h"
#include "entities/menu.h"

namespace flappy
{
	void InitGameOverScreen();
	void UpdateGameOverScreen(GameStats& gameStats, MenuButtons& buttons);
	void DrawGameOver1P(int score, MenuButtons& buttons);
	void DrawGameOver2P(int score1, int score2, MenuButtons& buttons);

}