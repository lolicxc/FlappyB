#include "gameOverScreen.h"
#include "utilities.h"

Texture2D gameOverText;

void flappy::InitGameOverScreen()
{
    gameOverText = LoadTexture("res/gameover.png");
}

void flappy::UpdateGameOverScreen(GameStats& gameStats, MenuButtons& buttons)
{
    buttons.resetButtState = GetButtonState(buttons.resetButton);
    if (buttons.resetButtState == 2) 
    {
        gameStats.gameStatus = SceneStatus::RESETGAME;
        return;
    }

   
    buttons.backToMenuButtState = GetButtonState(buttons.backMenuButton);
    if (buttons.backToMenuButtState == 2)
    {
        gameStats.gameStatus = SceneStatus::GAMEMENU;
        return;
    }
}

void flappy::DrawGameOver1P(int score, MenuButtons& buttons)
{
    DrawTexture(gameOverText, 0, 0, WHITE);
    DrawTextEx(paperFont, TextFormat("Score: %i", score), { 430, 280 }, 70, 1, BLACK);

    // Dibujar botones
    DrawButton(buttons.buttonSprite, buttons.resetButton, buttons.resetButtState);
    DrawTextEx(flappy::paperFont, "Main menu", { 10, 700 }, 40, 1, BLACK);
}


void flappy::DrawGameOver2P(int score1, int score2, MenuButtons& buttons)
{
    DrawTexture(gameOverText,0 ,0 , WHITE);
    DrawTextEx(flappy::paperFont, TextFormat("Player 1 score: %i", score1), { 300, 280 }, 70, 1,BLACK);
    DrawTextEx(flappy::paperFont, TextFormat("Player 2 score: %i", score2), { 300, 360 }, 70, 1, BLACK);

    // Dibujar botones
    DrawButton(buttons.buttonSprite, buttons.resetButton, buttons.resetButtState);
    DrawTextEx(flappy::paperFont, "Main menu", { 10, 700 }, 40, 1, BLACK);
  
}

