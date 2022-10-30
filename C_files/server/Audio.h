#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	Mix_Music* hMusic;
	Mix_Chunk* hWallSound;
	Mix_Chunk* hRacketSound;
} *Audio;

	bool InitAudio(Audio audio);
	void CleanupAudio(Audio audio);
	void PlayWallSound(Audio audio);
	void PlayRacketSound(Audio audio);
	void PlayMusic(Audio audio);
	void StopMusic(void);


	