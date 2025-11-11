#pragma once

#include "../utilities.h"
#include "raylib.h"
#include "player.h" 

namespace flappy
{
    struct Enemy
    {
        Rectangle enemyFigureDown;
        Rectangle enemyFigureUp;
        float speed;
        bool isAlive;


    };

    extern Enemy enemiesP1[];
    extern Enemy enemiesP2[];
    extern float spawnTimerP1;
    extern float spawnTimerP2;
    extern const int MAX_ENEMIES;

    
    void InitEnemy(Enemy enemyArray[], int maxEnemies);
    void CreateEnemy(Enemy enemyArray[], int maxEnemies, bool toLeft, bool twoPlayers);
    void UpdateEnemy(Enemy enemyArray[], int maxEnemies, float& spawnTimer, bool toLeft, bool twoPlayers);
    void DrawEnemy(Enemy enemyArray[], int maxEnemies);
    void CheckPlayerCollision(Enemy enemyArray[], int maxEnemies, Circle playerHitBox, bool& isHit);

  
    void InitAllEnemies(bool twoPlayers);
    void UpdateAllEnemies(bool twoPlayers);
    void DrawAllEnemies(bool twoPlayers);
    void CheckCollisionsWithPlayers(Player& player1, Player& player2, bool twoPlayers);

}