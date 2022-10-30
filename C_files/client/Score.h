#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int PlayerScore[MAX_CLIENT];	
	SDL_Texture* hTexFont;
	SDL_Rect ScoreDest[MAX_CLIENT];
	SDL_Color ScoreColor;
	TTF_Font* hFont;
	int FontWidth;
	int FontHeight;
} *Score;
	
	bool InitTTF(SDL_Renderer* gRenderer, Score score);
	void RenderScore(SDL_Renderer* gRenderer, Score score);
	void ResetScore(Score score);
	int getPlayerScore(int playernum, Score score);
	void SetPlayerScore(int playerScore[], Score score, int playerNr);