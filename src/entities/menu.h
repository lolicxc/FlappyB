#pragma once

#include <string>

#include "raylib.h"

#include "../utilities.h"

using namespace std;

namespace flappy
{
	struct MenuButtons
	{
		Texture2D buttonSprite;

		Rectangle backButton;
		Rectangle playButton;
		//Rectangle rulesButton;
		Rectangle play2PButton;
		Rectangle creditsButton;
		Rectangle backMenuButton;
		Rectangle resetButton;
		
		int backButtState;
		int playButtState;
		//int rulesButtState;
		int play2PButtState;
		int creditsButtState;
		int backToMenuButtState;
		int resetButtState;
	};

	void InitButtons(MenuButtons& buttons);
	void UpdateSceneMenus(GameStats& gameStats, MenuButtons& buttons);
	void DrawMenuTypeScene(GameStats gameStats, MenuButtons buttons);
}