#include "Audio.h"

Music mainMenuMusic;
Music gameMusicMusic;
Sound jumpSound;
//Sound clickSound;
//Sound shipSound;
//Sound explotion;
//Sound asteroidExpo;

void InitAudio()
{
    mainMenuMusic = LoadMusicStream("res/background.wav");
    gameMusicMusic = LoadMusicStream("res/gameplay.wav");
    jumpSound = LoadSound("res/jump.wav");
  /*  hoverSound = LoadSound("res/hover.wav");
    deadSound = LoadSound("res/shipSound.wav");
    clickSound = LoadSound("res/explotion.wav");
    scoreSound = LoadSound("res/asteroidExplotion.wav");*/
}

void UnloadAudio()
{
    UnloadMusicStream(mainMenuMusic);
    UnloadMusicStream(gameMusicMusic);
    UnloadSound(jumpSound);
 /*   UnloadSound(clickSound);
    UnloadSound(shipSound);*/
}
