#include "GameOverScreen.h"
#include "raylib.h"


namespace flappy
{
    void UpdateGameOverScreen(GameStats& gameStats, MenuButtons& buttons)
    {
        // Botón RESET (volver a jugar de una)
        buttons.resetButtState = GetButtonState(buttons.resetButton);
        if (buttons.resetButtState == 2)   // 2 = CLICK
        {
            gameStats.gameStatus = SceneStatus::RESETGAME;
            return;
        }

        // Botón VOLVER AL MENÚ
        buttons.backToMenuButtState = GetButtonState(buttons.backMenuButton);
        if (buttons.backToMenuButtState == 2)
        {
            gameStats.gameStatus = SceneStatus::GAMEMENU;
            return;
        }
    }
    void DrawGameOver1P(int score)
    {
        DrawText("GAME OVER", 300, 150, 80, RED);
        DrawText(TextFormat("Puntos: %i", score), 300, 280, 50, WHITE);
        DrawText("Presiona ENTER para volver al menu", 220, 380, 30, LIGHTGRAY);
    }

    void DrawGameOver2P(int score1, int score2)
    {
        DrawText("GAME OVER", 300, 150, 80, RED);
        DrawText(TextFormat("Jugador 1: %i", score1), 300, 280, 50, WHITE);
        DrawText(TextFormat("Jugador 2: %i", score2), 300, 340, 50, WHITE);
        DrawText("Presiona ENTER para volver al menu", 220, 420, 30, LIGHTGRAY);
    }
}