
// group 13 ... 13/5/2022  Yasir Riyadh
// Audio (sound effects and music) Task

#include "Audio.h"

bool InitAudio(Audio audio) {
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);	
	if((audio->hMusic = Mix_LoadMUS("music.wav")) == NULL) return false;	
	audio->hRacketSound = Mix_LoadWAV("racketsound.wav");
	if (!audio->hRacketSound)	return false;	
	audio->hWallSound = Mix_LoadWAV("bounce.wav");
	if (!audio->hWallSound)	return false;
	return true;
}
void CleanupAudio(Audio audio) {
	Mix_CloseAudio();	
	Mix_FreeChunk(audio->hWallSound);
	Mix_FreeChunk(audio->hRacketSound);
	Mix_FreeMusic(audio->hMusic);
	Mix_Quit();
}
void PlayWallSound(Audio audio) {
	Mix_PlayChannel(-1, audio->hWallSound, 0);
}
void PlayRacketSound(Audio audio) {
	Mix_PlayChannel(-1, audio->hRacketSound, 0);
}
void PlayMusic(Audio audio) {
	Mix_PlayMusic(audio->hMusic, -1);
}
void StopMusic(void) {
	Mix_HaltMusic();
}