#include "menu.h"
#include "../creditsScreen.h"

namespace flappy
{
	Vector2 recSize = { 90.0f, 50.0f };
	bool isOnButton = false;
	Texture2D pauseText;

	void DrawMainMenu(GameStats gameStats, MenuButtons buttons);
	//void DrawRulesMenu(GameStats gameStats, MenuButtons buttons);
	void DrawPause(GameStats gameStats, MenuButtons buttons);

	bool isPaused = false;

	bool IsMouseOverButton(Rectangle buttonRec)
	{
		Vector2 mousePos = GetMousePosition();

		float left = buttonRec.x - buttonRec.width / 2;
		float right = buttonRec.x + buttonRec.width / 2;
		float top = buttonRec.y + buttonRec.height / 2;
		float bottom = buttonRec.y - buttonRec.height / 2;

		if (mousePos.x >= left && mousePos.x <= right && mousePos.y <= top && mousePos.y >= bottom)
			return true;

		return false;
	}
	void InitButtons(MenuButtons& buttons)
	{
		buttons.buttonSprite = LoadTexture("res/button.png");
		buttons.mainmenu = LoadTexture("res/mainmenu.png");
		float menuButtonsPosX = GetScreenWidth() / 2;
		float backButtonPosX = 100.0f;
		float backButtonPosY = 720.0f;

		float resetButtonPosX = 100.0f;
		float resetButtonPosY = 720.0f;
		float goMenuButtonPosX = 100.0f;
		float goMenuButtonPosY = 720.0f;

		buttons.playButtState = 0;
		//buttons.rulesButtState = 0;
		buttons.creditsButtState = 0;
		buttons.backButtState = 0;
		buttons.backToMenuButtState = 0;
		buttons.resetButtState = 0;

		float buttonWidth = 110.0f;
		float buttonHeight = 72.0f;

		float playButtonPosy = 320.0f;
		//float rulesButtonPosy = 370.0f;
		float play2PButtonPosy = 430.0f;
		float creditButtonPosy = 550.0f;

		//posiciones de botones y tamanio de hitbox
		buttons.playButton = { menuButtonsPosX,playButtonPosy,buttonWidth,buttonHeight };
		buttons.play2PButton = { menuButtonsPosX, play2PButtonPosy, buttonWidth, buttonHeight };
		//buttons.rulesButton = { menuButtonsPosX,rulesButtonPosy,buttonWidth,buttonHeight };
		buttons.creditsButton = { menuButtonsPosX,creditButtonPosy,buttonWidth,buttonHeight };

		buttons.backButton = { backButtonPosX,backButtonPosY,buttonWidth,buttonHeight };

		buttons.resetButton = { resetButtonPosX,resetButtonPosY,buttonWidth,buttonHeight };
		buttons.backMenuButton = { goMenuButtonPosX,goMenuButtonPosY,buttonWidth,buttonHeight };
	}
	void UpdateSceneMenus(GameStats& gameStats, MenuButtons& buttons)
	{
		switch ((SceneStatus)gameStats.gameStatus)
		{
		case SceneStatus::GAMEMENU:

			buttons.playButtState = GetButtonState(buttons.playButton);
			//buttons.rulesButtState = GetButtonState(buttons.rulesButton);
			buttons.play2PButtState = GetButtonState(buttons.play2PButton);
			buttons.creditsButtState = GetButtonState(buttons.creditsButton);

			if (!IsMouseOverButton(buttons.playButton)
				/*&& !IsMouseOverButton(buttons.rulesButton)*/
				&& !IsMouseOverButton(buttons.creditsButton))
			{
				isOnButton = false;
			}
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
				&& IsMouseOverButton(buttons.playButton))
			{
				//PlaySFX(audio.clickSound);
				gameStats.gameStatus = SceneStatus::FIRSTGAME;
			}
			else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && IsMouseOverButton(buttons.play2PButton))
			{
				gameStats.gameStatus = SceneStatus::GAMEPLAY2P; // ?? modo 2 jugadores
			}
			//else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
			//	&& IsMouseOverButton(buttons.rulesButton))
			//{
			//	//PlaySFX(audio.clickSound);
			//	gameStats.gameStatus = SceneStatus::GAMERULES;
			//}
			else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
				&& IsMouseOverButton(buttons.creditsButton))
			{
				//PlaySFX(audio.clickSound);
				gameStats.gameStatus = SceneStatus::GAMECREDITS;
			}
			break;

			//case SceneStatus::GAMERULES:

			//	buttons.backButtState = GetButtonState(buttons.backButton);

			//	if (!IsMouseOverButton(buttons.backButton))
			//		isOnButton = false;

			//	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
			//		&& IsMouseOverButton(buttons.backButton))
			//	{
			//		//PlaySFX(audio.clickSound);
			//		gameStats.gameStatus = SceneStatus::GAMEMENU;
			//	}
			//	break;

		case SceneStatus::GAMECREDITS:

			UpdateCredits(gameStats);
			buttons.backButtState = GetButtonState(buttons.backButton);

			if (!IsMouseOverButton(buttons.backButton))
				isOnButton = false;

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
				&& IsMouseOverButton(buttons.backButton))
			{
				//PlaySFX(audio.clickSound);
				gameStats.gameStatus = SceneStatus::GAMEMENU;
			}
			break;

		case SceneStatus::FIRSTGAME:

			buttons.backToMenuButtState = GetButtonState(buttons.backMenuButton);

			if (!IsMouseOverButton(buttons.backMenuButton))
				isOnButton = false;

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
				&& IsMouseOverButton(buttons.backMenuButton))
			{
				//PlaySFX(audio.clickSound);
				gameStats.gameStatus = SceneStatus::GAMEMENU;
			}
			if (IsKeyPressed(KEY_SPACE))
			{
				gameStats.gameStatus = SceneStatus::GAMEPLAY;
			}
			break;

		case SceneStatus::GAMEPLAY:

			if (IsKeyPressed(KEY_SPACE))
			{
				isPaused = true;
				gameStats.previousGameplayMode = gameStats.gameStatus; // guardo modo 1P
				gameStats.gameStatus = SceneStatus::GAMEPAUSE;
			}
			break;

		case SceneStatus::GAMEPLAY2P:
			if (IsKeyPressed(KEY_SPACE))
			{
				isPaused = true;
				gameStats.previousGameplayMode = gameStats.gameStatus; // guardo modo 2P
				gameStats.gameStatus = SceneStatus::GAMEPAUSE;
			}
			break;
		case SceneStatus::GAMEPAUSE:

			buttons.backToMenuButtState = GetButtonState(buttons.backMenuButton);
			buttons.resetButtState = GetButtonState(buttons.resetButton);

			if (IsKeyPressed(KEY_SPACE))
				isPaused = false;

			if (!isPaused)
				gameStats.gameStatus = gameStats.previousGameplayMode; 

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && IsMouseOverButton(buttons.resetButton))
			{
				gameStats.gameStatus = SceneStatus::RESETGAME;
			}
			break;

		case SceneStatus::GAMEEND:

			buttons.backToMenuButtState = GetButtonState(buttons.backMenuButton);
			buttons.resetButtState = GetButtonState(buttons.resetButton);

			if (!IsMouseOverButton(buttons.backMenuButton)
				&& !IsMouseOverButton(buttons.resetButton))
				isOnButton = false;

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
				&& IsMouseOverButton(buttons.backMenuButton))
			{
				//PlaySFX(audio.clickSound);
				isOnButton = false;
				gameStats.gameStatus = SceneStatus::GAMEMENU;
			}
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)
				&& IsMouseOverButton(buttons.resetButton))
			{
				//PlaySFX(audio.clickSound);
				gameStats.gameStatus = SceneStatus::RESETGAME;
			}
			//if (!IsKeyPressed(KEY_SPACE) && IsKeyReleased(KEY_SPACE))
			//{
			//	//PlaySFX(audio.clickSound);
			//	gameStats.gameStatus = SceneStatus::GAMEPLAY;
			//}
			break;

		default:
			break;
		}
	}
	void DrawMenuTypeScene(GameStats gameStats, MenuButtons buttons)
	{
		int auxPosX = 10;
		int auxPosY = 10;
		int auxFont = 10;

		switch ((SceneStatus)gameStats.gameStatus)
		{
		case SceneStatus::GAMEMENU:

			DrawText("v0.4", auxPosX, auxPosY, auxFont, WHITE);
			DrawMainMenu(gameStats, buttons);

			break;

			//case SceneStatus::GAMERULES:
			//	break;

		case SceneStatus::GAMECREDITS:

			DrawCreditsMenu();

			break;

		case SceneStatus::FIRSTGAME:
		{

			Vector2 pos = { 300, 100 };
			float fontSize = 50.0f;
			float spacing = 2.0f;
			Color tint = WHITE;

			DrawTextEx(flappy::paperFont, "Press SPACE to START", pos, fontSize, spacing, tint);
			DrawButton(buttons.buttonSprite, buttons.backMenuButton, buttons.backToMenuButtState);
			DrawTextEx(flappy::paperFont, "Main menu", {10, 700}, 40, 1, BLACK);

			break;
		}

		case SceneStatus::GAMEPLAY:

			if (!IsKeyPressed(KEY_W) && IsKeyReleased(KEY_W))
			{
				//PlaySFX(audio.clickSound);
				gameStats.gameStatus = SceneStatus::GAMEPAUSE;
			}
			break;

		case SceneStatus::GAMEPAUSE:

			DrawPause(gameStats, buttons);
			break;

		case SceneStatus::GAMEEND:

			DrawPause(gameStats, buttons);
			break;

		default:
			break;
		}
	}
	Vector2 GetTextPositionCenteredOnButton(const Rectangle& button, const char* text, Font font, float fontSize, float spacing)
	{
		Vector2 textSize = MeasureTextEx(font, text, fontSize, spacing);
		Vector2 pos;
		pos.x = button.x - textSize.x / 2.0f;
		pos.y = button.y - textSize.y / 2.0f;
		return pos;
	}
	void DrawMainMenu(GameStats gameStats, MenuButtons buttons)
	{
		if (gameStats.gameStatus == SceneStatus::GAMEMENU)
		{
			
			int defaultFontSize = 45;  
			int exitFontSize = 15;

			float spacing = 2.0f; 
			Color textColor = BLACK;

			DrawTexture(buttons.mainmenu, 0, 0, WHITE);
			DrawButton(buttons.buttonSprite, buttons.playButton, buttons.playButtState);
			DrawButton(buttons.buttonSprite, buttons.play2PButton, buttons.play2PButtState);
			DrawButton(buttons.buttonSprite, buttons.creditsButton, buttons.creditsButtState);

			Vector2 pos;

			//Play
			pos = GetTextPositionCenteredOnButton(buttons.playButton, "Single player", flappy::paperFont, (float)gameStats.fontSize, 2.0f);
			pos.x += 50;
			DrawTextEx(flappy::paperFont, "Single player", pos, defaultFontSize, 2.0f, BLACK);

			//Play 2P
			pos = GetTextPositionCenteredOnButton(buttons.play2PButton, "Multiplayer", flappy::paperFont, (float)gameStats.fontSize, 2.0f);
			pos.x += 50;
			DrawTextEx(flappy::paperFont, "Multiplayer", pos, defaultFontSize, 2.0f, BLACK);

			//Credits
			pos = GetTextPositionCenteredOnButton(buttons.creditsButton, "Credits", flappy::paperFont, (float)gameStats.fontSize, 2.0f);
			pos.x += 20;
			DrawTextEx(flappy::paperFont, "Credits", pos, defaultFontSize, 2.0f, BLACK);

		}
	}

	/*void DrawRulesMenu(GameStats gameStats, MenuButtons buttons)
	{
		if (gameStats.gameStatus == SceneStatus::GAMERULES)
		{
			int titleFontSize = 50;
			int defaultFontSize = 20;
			int exitFontSize = 20;

			int LineText1PosX = GetScreenWidth() / 2 - 100;
			int LineText1PosY = 100;

			int LineText2PosX = 100;
			int LineText2PosY = 230;

			int LineText3PosX = 100;
			int LineText3PosY = 280;

			int LineText4PosX = 100;
			int LineText4PosY = 310;

			int LineText5PosX = 100;
			int LineText5PosY = 380;

			int LineText6PosX = 100;
			int LineText6PosY = 450;

			int LineText7PosX = 100;
			int LineText7PosY = 480;

			int LineText8PosX = 100;
			int LineText8PosY = 510;

			int LineText9PosX = 100;
			int LineText9PosY = 650;

			int LineText0PosX = 75;
			int LineText0PosY = 705;

			Color textColor = BLACK;

			DrawButton(buttons.backButton, buttons.backButtState);

			DrawText("RULES", LineText1PosX, LineText1PosY, titleFontSize, textColor);

			DrawText("-To MOVE use LEFT Mouse Button and to SHOT use RIGHT mouse buton",
				LineText2PosX, LineText2PosY, defaultFontSize, textColor);
			DrawText("-In normal mode Destroy all Neufars to win.",
				LineText3PosX, LineText3PosY, defaultFontSize, textColor);
			DrawText("-In endless mode survive as long as you can.",
				LineText4PosX, LineText4PosY, defaultFontSize, textColor);
			DrawText("-You will have 3 lives. If you get touch by a neufar, you lose 1 life.",
				LineText5PosX, LineText5PosY, defaultFontSize, textColor);
			DrawText("TURTLE dont care about anything. But take care, they can change neufar direction !!",
				LineText6PosX, LineText6PosY, defaultFontSize, textColor);
			DrawText("FROGS loves water but we cant explain why their smell slows you down if they touch you.",
				LineText7PosX, LineText7PosY, defaultFontSize, textColor);
			DrawText("The PINK PETALS can reestore 1 life, if you are not full healt.",
				LineText8PosX, LineText8PosY, defaultFontSize, textColor);
			DrawText("-Use spacebar to pause game at any moment.",
				LineText9PosX, LineText9PosY, defaultFontSize, textColor);
			DrawText("Back", LineText0PosX, LineText0PosY, exitFontSize, textColor);
		}
	}*/
	
	void DrawPause(GameStats gameStats, MenuButtons buttons)
	{
		if (gameStats.gameStatus != SceneStatus::GAMEPAUSE)
			return; // Salir si no estamos en pausa
		int defaultFontSize = 50;

		Color textColor = BLACK;
		pauseText = LoadTexture("res/pause.png");
		// Instrucción
		DrawTexture(pauseText, 0, 0, WHITE);
		DrawTextEx(flappy::paperFont, "Press SPACEBAR to resume", { 250, 300 }, defaultFontSize, 1, textColor);

		// Botones
		DrawButton(buttons.buttonSprite, buttons.resetButton, buttons.resetButtState);
		DrawButton(buttons.buttonSprite, buttons.backMenuButton, buttons.backToMenuButtState);
		DrawTextEx(flappy::paperFont, "Main menu", { 10, 700 }, 40, 1, BLACK);
	
	}


	int GetButtonState(Rectangle button)
	{
		Vector2 mouse = GetMousePosition();

		if (IsMouseOverButton(button))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				return 2;
			}
			else
			{
				if (!isOnButton)
				{
					//PlaySFX(audio.overSound);
					isOnButton = true;
				}
				return 1;
			}
		}
		return 0;
	}
	void DrawButton(Texture2D buttonSprite, Rectangle button, int state)
	{


		float frameWidth = (float)buttonSprite.width / 2.0f;
		float frameHeight = (float)buttonSprite.height;
		float offsetX = 30.0f;

		Rectangle source = { state * frameWidth, 0, frameWidth, frameHeight };

		Rectangle dest = { button.x - frameWidth / 2 + offsetX, button.y - frameHeight / 2,
						   frameWidth, frameHeight };



		Vector2 origin = { 0, 0 };
		DrawTexturePro(buttonSprite, source, dest, origin, 0, WHITE);
	}
}