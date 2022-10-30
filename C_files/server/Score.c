
// group 13 ... 13/5/2022  Yasir Riyadh
// Score system Task

#pragma warning(disable : 4996)
#include "Score.h"

bool InitTTF(SDL_Renderer* gRenderer, Score score)
{
    score->FontWidth = 0;
    score->FontHeight = 0;
    score->ScoreColor.r = 255; score->ScoreColor.g = 255; score->ScoreColor.b = 255;
    ResetScore(score);
    if (TTF_Init() == -1) {
        fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Delay(5000);
        return false;
    }

    score->hFont = TTF_OpenFont("upheavtt.ttf", FONTSIZE);
    if (!score->hFont) {
        fprintf(stderr, "Failed the load the font: %s\n", TTF_GetError());
        SDL_Delay(5000);
        return false;
    }

    SDL_Surface* hSurface;
    hSurface = TTF_RenderText_Solid(score->hFont, "00", score->ScoreColor);
    if (!hSurface) {
        fprintf(stderr, "Failed to render text surface: %s\n", TTF_GetError());
        SDL_Delay(5000);
        return false;
    }

    score->hTexFont = SDL_CreateTextureFromSurface(gRenderer, hSurface);
    if (!score->hTexFont) {
        fprintf(stderr, "Failed to create font texture: %s\n", TTF_GetError());
        SDL_Delay(5000);
        return false;
    }

    score->FontWidth = hSurface->w;
    score->FontHeight = hSurface->h;
    SDL_FreeSurface(hSurface);
    for (int i = 0; i < MAX_CLIENT; i++) {
        score->ScoreDest[i].w = score->FontWidth;
        score->ScoreDest[i].h = score->FontHeight;
    }

    score->ScoreDest[0].x = SCREEN_WIDTH / 2 - 18;
    score->ScoreDest[0].y = SCREEN_HEIGHT - FONTSIZE;
    score->ScoreDest[1].x = SCREEN_WIDTH / 2 - 18; 
    score->ScoreDest[1].y = 0;
    score->ScoreDest[2].x = 14;
    score->ScoreDest[2].y = SCREEN_HEIGHT / 2 - 18;
    score->ScoreDest[3].x = (int) (SCREEN_WIDTH - 1.5 * (double) FONTSIZE);
    score->ScoreDest[3].y = SCREEN_HEIGHT / 2 - 18;


    return true;
}

void RenderScore(SDL_Renderer* gRenderer, Score score) {

    char str[3];

    for(int i = 0; i < MAX_CLIENT; i++)
    {
        sprintf(str, "%d", score->PlayerScore[i]);
        SDL_Surface* hSurface = TTF_RenderText_Solid(score->hFont, str, score->ScoreColor);
        score->hTexFont = SDL_CreateTextureFromSurface(gRenderer, hSurface);
        SDL_FreeSurface(hSurface);
        SDL_RenderCopyEx(gRenderer, score->hTexFont, NULL, &score->ScoreDest[i], 0, NULL, SDL_FLIP_NONE);
    }
}

void ResetScore(Score score) {
    for (int i = 0; i < MAX_CLIENT; i++)  score->PlayerScore[i] = 0;
}
int getPlayerScore(int playernum, Score score) {
    return score->PlayerScore[playernum];
}
void SetPlayerScore(int playerScore[], Score score, int playerNr)
{
    if(playerNr == 0)
    {
        score->PlayerScore[0] = playerScore[0];
        score->PlayerScore[1] = playerScore[1];
        score->PlayerScore[2] = playerScore[2];
        score->PlayerScore[3] = playerScore[3];
    }

    else if(playerNr == 1)
    {
        score->PlayerScore[0] = playerScore[1];
        score->PlayerScore[1] = playerScore[0];
        score->PlayerScore[2] = playerScore[3];
        score->PlayerScore[3] = playerScore[2];
    }

    else if(playerNr == 2)
    {
        score->PlayerScore[0] = playerScore[2];
        score->PlayerScore[1] = playerScore[3];
        score->PlayerScore[2] = playerScore[1];
        score->PlayerScore[3] = playerScore[0];
    }

    else if(playerNr == 3)
    {
        score->PlayerScore[0] = playerScore[3];
        score->PlayerScore[1] = playerScore[2];
        score->PlayerScore[2] = playerScore[0];
        score->PlayerScore[3] = playerScore[1];
    }
}
