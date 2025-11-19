#pragma once
#include "raylib.h"
#include <string>
#include "utilities.h"

namespace flappy
{
    struct HowButton
    {
        std::string text;
        Rectangle rect;
        Color color;
    };

    void InitHowToPlay();
    void UpdateHowToPlay(GameStats& gameStats);
    void DrawHowToScreen();
}
