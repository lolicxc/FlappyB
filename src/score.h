#pragma once

namespace flappy
{
    struct Player; 
    extern int score1;
    extern int score2;

    void InitScore();
    void UpdateScore1(Player& player);
    void UpdateScore2(Player& player);
    void ResetScore();
    void DrawScore();
    void DrawScore2();
}
