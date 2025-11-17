#pragma once

namespace flappy
{
    struct Player; 

    void InitScore();
    void UpdateScore(Player& player);
    void ResetScore();
    int GetScore();
    void DrawScore();
}
