#include "creditsScreen.h"
#include "raylib.h"
#include "utilities.h"

namespace flappy
{
	TextButton creditButtons[4];
	bool mousePressedLastFrame = false;
	Texture2D creditsText;
	void InitCredits()
	{
		Color defaultColor = BLACK;
		creditsText = LoadTexture("res/credits.png");
		creditButtons[0] = { "Francisco Jonas", {370, 250, 0, 0}, "https://4franjonas2.itch.io/", defaultColor };
		creditButtons[1] = { "Dolores Caparroz", {370, 300, 0, 0}, "https://lolicxc.itch.io/", defaultColor };
		creditButtons[2] = { "Dolores Caparroz", {370, 470, 0, 0}, "https://www.artstation.com/mariadolorescaparroz", defaultColor };

		// back
		creditButtons[3] = { "Back", {75, 705, 0, 0}, "", defaultColor };
	}

	void UpdateCredits(GameStats& gameStats)
	{
		if (gameStats.gameStatus != SceneStatus::GAMECREDITS) return;

		Vector2 mp = GetMousePosition();
		bool mousePressed = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

		for (int i = 0; i < 4; i++)
		{
			// actualizar tamaño
			creditButtons[i].rect.width = MeasureText(creditButtons[i].text.c_str(), 40);
			creditButtons[i].rect.height = 40;

			// hover
			if (CheckCollisionPointRec(mp, creditButtons[i].rect))
			{
				creditButtons[i].color = BLUE;

				if (mousePressed && !mousePressedLastFrame)
				{
					if (creditButtons[i].url.empty())
						gameStats.gameStatus = SceneStatus::GAMEMENU;
					else
						OpenURL(creditButtons[i].url.c_str());
				}
			}
			else
			{
				creditButtons[i].color = BLACK;
			}
		}

		mousePressedLastFrame = mousePressed;
	}

	void DrawCreditsMenu()
	{
		DrawTexture(creditsText, 0, 0, WHITE);

		for (int i = 0; i < 4; i++)
		{
			DrawTextEx(paperFont,
				creditButtons[i].text.c_str(),
				{ creditButtons[i].rect.x, creditButtons[i].rect.y },
				40,     // font size
				1,      // spacing
				creditButtons[i].color);

		}
	}
}
