#include "Audio.h"

 Music mainMenuMusic;
 Music gameMusicMusic;
 Sound jumpSound;
 Sound hoverSound;
 Sound deadSound;
 Sound clickSound;
 Sound scoreSound;

void InitAudio()
{
	mainMenuMusic = LoadMusicStream("res/background.wav");
	gameMusicMusic = LoadMusicStream("res/gameplay.wav");
	jumpSound = LoadSound("res/jump.wav");
	hoverSound = LoadSound("res/hover.wav");
	deadSound = LoadSound("res/click.wav");
	clickSound = LoadSound("res/dead.wav");
	scoreSound = LoadSound("res/score.wav");
}

void UnloadAudio()
{
	UnloadMusicStream(mainMenuMusic);
	UnloadMusicStream(gameMusicMusic);
	UnloadSound(jumpSound);
	UnloadSound(hoverSound);
	UnloadSound(deadSound);
	UnloadSound(clickSound);
	UnloadSound(scoreSound);

}
