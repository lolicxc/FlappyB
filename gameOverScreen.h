#pragma once
#include "utilities.h"
namespace flappy
{
    void UpdateGameOverScreen(GameStats& gameStats, MenuButtons& buttons);
    void DrawGameOver1P(int score);
    void DrawGameOver2P(int score1, int score2);
}