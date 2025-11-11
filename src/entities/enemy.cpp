#include "enemy.h"

namespace flappy
{
    const int MAX_ENEMIES = 5;

    Enemy enemiesP1[MAX_ENEMIES];
    Enemy enemiesP2[MAX_ENEMIES];

    float spawnTimerP1 = 0.0f;
    float spawnTimerP2 = 0.0f;


    void CheckArenaLimits(Enemy enemyArray[], int i, bool toLeft)
    {
        if (!enemyArray[i].isAlive) return;

        if (toLeft)
        {
            // Jugador 1: se mueve hacia la izquierda
            if (enemyArray[i].enemyFigureDown.x + enemyArray[i].enemyFigureDown.width < 0)
                enemyArray[i].isAlive = false;
        }
        else
        {
            // Jugador 2: se mueve hacia la derecha
            if (enemyArray[i].enemyFigureDown.x > GetScreenWidth())
                enemyArray[i].isAlive = false;
        }
    }

    void InitEnemy(Enemy enemyArray[], int maxEnemies)
    {
        for (int i = 0; i < maxEnemies; i++)
        {
            enemyArray[i].enemyFigureDown = { 0, 0, 50, 600 };
            enemyArray[i].enemyFigureUp = { 0, 0, 50, 600 };
            enemyArray[i].speed = 200.0f;
            enemyArray[i].isAlive = false;
        }
    }

    void CreateEnemy(Enemy enemyArray[], int maxEnemies, bool toLeft, bool twoPlayers)
    {
        int minRangeYPos = 200;
        int maxRangeYPos = 700;
        int minEmptySpace = 170;

        for (int i = 0; i < maxEnemies; i++)
        {
            if (!enemyArray[i].isAlive)
            {
                float startX = 0.0f;

                if (!twoPlayers)
                {
                    // Modo 1 jugador: desde la derecha de la pantalla
                    startX = static_cast<float>(GetScreenWidth());
                }
                else
                {
                    if (toLeft)
                        startX = static_cast<float>(GetScreenWidth() / 2 + 50); // Jugador 1: mitad derecha del centro
                    else
                        startX = static_cast<float>(GetScreenWidth() / 2 - 50); // Jugador 2: mitad izquierda del centro
                }

                enemyArray[i].enemyFigureDown.x = startX;
                enemyArray[i].enemyFigureDown.y = static_cast<float>(GetRandomValue(minRangeYPos, maxRangeYPos));
                enemyArray[i].enemyFigureUp.x = enemyArray[i].enemyFigureDown.x;
                enemyArray[i].enemyFigureUp.y = enemyArray[i].enemyFigureDown.y - enemyArray[i].enemyFigureUp.height - minEmptySpace;

                enemyArray[i].isAlive = true;
                break;
            }
        }
    }


    void UpdateEnemy(Enemy enemyArray[], int maxEnemies, float& spawnTimer, bool toLeft, bool twoPlayers)
    {
        spawnTimer += GetFrameTime();
        float spawnDelay = 2.0f;

        if (spawnTimer >= spawnDelay)
        {
            CreateEnemy(enemyArray, maxEnemies, toLeft, twoPlayers);
            spawnTimer = 0;
        }

        for (int i = 0; i < maxEnemies; i++)
        {
            if (!enemyArray[i].isAlive) continue;

            if (!twoPlayers)
            {
             
                enemyArray[i].enemyFigureDown.x -= enemyArray[i].speed * GetFrameTime();
            }
            else
            {
                if (toLeft)
                    enemyArray[i].enemyFigureDown.x -= enemyArray[i].speed * GetFrameTime();
                else
                    enemyArray[i].enemyFigureDown.x += enemyArray[i].speed * GetFrameTime();
            }

            enemyArray[i].enemyFigureUp.x = enemyArray[i].enemyFigureDown.x;

            CheckArenaLimits(enemyArray, i, toLeft);
        }
    }


    void DrawEnemy(Enemy enemyArray[], int maxEnemies)
    {
        for (int i = 0; i < maxEnemies; i++)
        {
            if (!enemyArray[i].isAlive) continue;
            DrawRectangleRec(enemyArray[i].enemyFigureDown, RED);
            DrawRectangleRec(enemyArray[i].enemyFigureUp, RED);
        }
    }

    void CheckPlayerCollision(Enemy enemyArray[], int maxEnemies, Circle playerHitBox, bool& isHit)
    {
        for (int i = 0; i < maxEnemies; i++)
        {
            if (!enemyArray[i].isAlive) continue;

            if (CheckCollisionCircleRec(playerHitBox.pos, playerHitBox.rad, enemyArray[i].enemyFigureDown) ||
                CheckCollisionCircleRec(playerHitBox.pos, playerHitBox.rad, enemyArray[i].enemyFigureUp))
            {
                isHit = true;
                return;
            }
        }
    }

 

    void InitAllEnemies(bool twoPlayers)
    {
        InitEnemy(enemiesP1, MAX_ENEMIES);
        if (twoPlayers)
            InitEnemy(enemiesP2, MAX_ENEMIES);
    }

    void UpdateAllEnemies(bool twoPlayers)
    {
        if (!twoPlayers)
            UpdateEnemy(enemiesP1, MAX_ENEMIES, spawnTimerP1, true, false); 
        else
        {
            UpdateEnemy(enemiesP1, MAX_ENEMIES, spawnTimerP1, true, true);  
            UpdateEnemy(enemiesP2, MAX_ENEMIES, spawnTimerP2, false, true); 
        }
    }


    void DrawAllEnemies(bool twoPlayers)
    {
        DrawEnemy(enemiesP1, MAX_ENEMIES);
        if (twoPlayers)
            DrawEnemy(enemiesP2, MAX_ENEMIES);
    }

    void CheckCollisionsWithPlayers(Player& player1, Player& player2, bool twoPlayers)
    {
        CheckPlayerCollision(enemiesP1, MAX_ENEMIES, player1.playerHitbox, player1.playerGotHit);
        if (twoPlayers)
            CheckPlayerCollision(enemiesP2, MAX_ENEMIES, player2.playerHitbox, player2.playerGotHit);
    }
}
