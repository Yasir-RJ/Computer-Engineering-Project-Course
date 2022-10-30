#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL.h>

#include "racket.h"
#include "arena.h"
#include "defs.h"
#include "Score.h"

#define HEIGHT 12
#define WIDTH 64

struct racket
{
    int RACKET_POS_X;
    int RACKET_POS_Y;
    int RACKET_WIDTH;
    int RACKET_HEIGHT;
    float RACKET_VEL;
    SDL_Texture *RACKET_TEXTURE;
    SDL_Rect RACKET_RECT;
};

Racket racketCreate(int playerNr, SDL_Renderer *gRenderer)
{
    Racket tmp = malloc(sizeof(struct racket));
    SDL_Surface *tmpSurface = SDL_LoadBMP("racket.bmp");
    tmp->RACKET_TEXTURE = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);

    if(playerNr == 0)
    {
        tmp->RACKET_POS_X = 352;
        tmp->RACKET_POS_Y = 672;
    }

    else if(playerNr == 1)
    {
        tmp->RACKET_POS_X = 352;
        tmp->RACKET_POS_Y = 88;
    }

    else if(playerNr == 2)
    {
        tmp->RACKET_POS_X = 60;
        tmp->RACKET_POS_Y = 380;
    }

    else if(playerNr == 3)
    {
        tmp->RACKET_POS_X = 644;
        tmp->RACKET_POS_Y = 380;
    }

    tmp->RACKET_WIDTH = WIDTH;
    tmp->RACKET_HEIGHT = HEIGHT;
    tmp->RACKET_VEL = 0;
    tmp->RACKET_RECT.x = tmp->RACKET_POS_X;
    tmp->RACKET_RECT.y = tmp->RACKET_POS_Y;
    tmp->RACKET_RECT.w = tmp->RACKET_WIDTH;
    tmp->RACKET_RECT.h = tmp->RACKET_HEIGHT;

    tmpSurface = NULL;

    return tmp;
}

void racketRender(int playerNr, Racket tmp[], SDL_Renderer *gRenderer)
{
    SDL_Rect rectRacketColor[4];

    rectRacketColor[0].x = 0;
    rectRacketColor[0].y = 0;
    rectRacketColor[0].w = 64;
    rectRacketColor[0].h = 12;

    rectRacketColor[1].x = 0;
    rectRacketColor[1].y = 12;
    rectRacketColor[1].w = 64;
    rectRacketColor[1].h = 12;

    rectRacketColor[2].x = 0;
    rectRacketColor[2].y = 24;
    rectRacketColor[2].w = 64;
    rectRacketColor[2].h = 12;

    rectRacketColor[3].x = 0;
    rectRacketColor[3].y = 36;
    rectRacketColor[3].w = 64;
    rectRacketColor[3].h = 12;

    if(playerNr == 0)
    {
        SDL_RenderCopyEx(gRenderer, tmp[0]->RACKET_TEXTURE, &rectRacketColor[0], &tmp[0]->RACKET_RECT, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(gRenderer, tmp[1]->RACKET_TEXTURE, &rectRacketColor[1], &tmp[1]->RACKET_RECT, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(gRenderer, tmp[2]->RACKET_TEXTURE, &rectRacketColor[2], &tmp[2]->RACKET_RECT, 90, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(gRenderer, tmp[3]->RACKET_TEXTURE, &rectRacketColor[3], &tmp[3]->RACKET_RECT, 90, NULL, SDL_FLIP_NONE);
    }

    else if(playerNr == 1)
    {
        SDL_RenderCopyEx(gRenderer, tmp[0]->RACKET_TEXTURE, &rectRacketColor[1], &tmp[0]->RACKET_RECT, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(gRenderer, tmp[1]->RACKET_TEXTURE, &rectRacketColor[0], &tmp[1]->RACKET_RECT, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(gRenderer, tmp[2]->RACKET_TEXTURE, &rectRacketColor[3], &tmp[2]->RACKET_RECT, 90, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(gRenderer, tmp[3]->RACKET_TEXTURE, &rectRacketColor[2], &tmp[3]->RACKET_RECT, 90, NULL, SDL_FLIP_NONE);
    }

    else if(playerNr == 2)
    {
        SDL_RenderCopyEx(gRenderer, tmp[0]->RACKET_TEXTURE, &rectRacketColor[2], &tmp[0]->RACKET_RECT, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(gRenderer, tmp[1]->RACKET_TEXTURE, &rectRacketColor[3], &tmp[1]->RACKET_RECT, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(gRenderer, tmp[2]->RACKET_TEXTURE, &rectRacketColor[1], &tmp[2]->RACKET_RECT, 90, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(gRenderer, tmp[3]->RACKET_TEXTURE, &rectRacketColor[0], &tmp[3]->RACKET_RECT, 90, NULL, SDL_FLIP_NONE);
    }

    else if(playerNr == 3)
    {
        SDL_RenderCopyEx(gRenderer, tmp[0]->RACKET_TEXTURE, &rectRacketColor[3], &tmp[0]->RACKET_RECT, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(gRenderer, tmp[1]->RACKET_TEXTURE, &rectRacketColor[2], &tmp[1]->RACKET_RECT, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(gRenderer, tmp[2]->RACKET_TEXTURE, &rectRacketColor[0], &tmp[2]->RACKET_RECT, 90, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(gRenderer, tmp[3]->RACKET_TEXTURE, &rectRacketColor[1], &tmp[3]->RACKET_RECT, 90, NULL, SDL_FLIP_NONE);
    }

    return;
}

void RacketRenderFinish(Racket tmp[], SDL_Renderer *gRenderer, Score score, int playerNr)
{
    for(int i = 0; i < MAX_CLIENT; i++)
    {
        tmp[i]->RACKET_POS_X = 128;
        tmp[i]->RACKET_POS_Y = 154 * (1 + i);

        tmp[i]->RACKET_RECT.x = 128;
        tmp[i]->RACKET_RECT.y = 154 * (1 + i);
    }

    if(playerNr == 0)
    {
        score->ScoreDest[0].x = 256;
        score->ScoreDest[0].y = 150;
        score->ScoreDest[1].x = 256;
        score->ScoreDest[1].y = 300;
        score->ScoreDest[2].x = 256;
        score->ScoreDest[2].y = 450;
        score->ScoreDest[3].x = 256;
        score->ScoreDest[3].y = 600;
    }

    else if(playerNr == 1)
    {
        score->ScoreDest[0].x = 256;
        score->ScoreDest[0].y = 300;
        score->ScoreDest[1].x = 256;
        score->ScoreDest[1].y = 150;
        score->ScoreDest[2].x = 256;
        score->ScoreDest[2].y = 600;
        score->ScoreDest[3].x = 256;
        score->ScoreDest[3].y = 450;
    }

    else if(playerNr == 2)
    {
        score->ScoreDest[0].x = 256;
        score->ScoreDest[0].y = 450;
        score->ScoreDest[1].x = 256;
        score->ScoreDest[1].y = 600;
        score->ScoreDest[2].x = 256;
        score->ScoreDest[2].y = 300;
        score->ScoreDest[3].x = 256;
        score->ScoreDest[3].y = 150;
    }

    else if(playerNr == 3)
    {
        score->ScoreDest[0].x = 256;
        score->ScoreDest[0].y = 600;
        score->ScoreDest[1].x = 256;
        score->ScoreDest[1].y = 450;
        score->ScoreDest[2].x = 256;
        score->ScoreDest[2].y = 150;
        score->ScoreDest[3].x = 256;
        score->ScoreDest[3].y = 300;
    }

    SDL_Rect rectRacketColor[4];

    rectRacketColor[0].x = 0;
    rectRacketColor[0].y = 0;
    rectRacketColor[0].w = 64;
    rectRacketColor[0].h = 12;

    rectRacketColor[1].x = 0;
    rectRacketColor[1].y = 12;
    rectRacketColor[1].w = 64;
    rectRacketColor[1].h = 12;

    rectRacketColor[2].x = 0;
    rectRacketColor[2].y = 24;
    rectRacketColor[2].w = 64;
    rectRacketColor[2].h = 12;

    rectRacketColor[3].x = 0;
    rectRacketColor[3].y = 36;
    rectRacketColor[3].w = 64;
    rectRacketColor[3].h = 12;

    SDL_RenderCopyEx(gRenderer, tmp[0]->RACKET_TEXTURE, &rectRacketColor[0], &tmp[0]->RACKET_RECT, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer, tmp[1]->RACKET_TEXTURE, &rectRacketColor[1], &tmp[1]->RACKET_RECT, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer, tmp[2]->RACKET_TEXTURE, &rectRacketColor[2], &tmp[2]->RACKET_RECT, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer, tmp[3]->RACKET_TEXTURE, &rectRacketColor[3], &tmp[3]->RACKET_RECT, 0, NULL, SDL_FLIP_NONE);

    return;
}

Racket racketUpdate(Racket tmp, bool racketKeyLeft, bool racketKeyRight, Arena arena)
{
    if(racketKeyLeft == true && racketKeyRight == false && getArenaSWCorner(arena)->w < tmp->RACKET_POS_X)
        tmp->RACKET_VEL = -256 / 60;

    else if(racketKeyLeft == false && racketKeyRight == true && tmp->RACKET_POS_X + tmp->RACKET_WIDTH < getArenaSECorner(arena)->x)
        tmp->RACKET_VEL = 256 / 60;

    else
        tmp->RACKET_VEL = 0;

    tmp->RACKET_POS_X += tmp->RACKET_VEL;
    tmp->RACKET_RECT.x = tmp->RACKET_POS_X;

    return tmp;
}

int getRacketHeight(Racket tmp){return tmp->RACKET_HEIGHT;}
int getRacketWidth(Racket tmp){return tmp->RACKET_WIDTH;}
int getRacketPosX(Racket tmp){return tmp->RACKET_POS_X;}
int getRacketPosY(Racket tmp){return tmp->RACKET_POS_Y;}
int getRacketVel(Racket tmp){return tmp->RACKET_VEL;}
void setRacketPosX(Racket tmp, int xPos)
{
    tmp->RACKET_POS_X = xPos;
    tmp->RACKET_RECT.x = tmp->RACKET_POS_X;
}
void setRacketPosY(Racket tmp, int yPos)
{
    tmp->RACKET_POS_Y = yPos;
    tmp->RACKET_RECT.y = tmp->RACKET_POS_Y;
}
void setRacketWidth(Racket tmp, int newWidth){tmp->RACKET_WIDTH = newWidth;}
void setRacketHeight(Racket tmp, int newHeight){tmp->RACKET_HEIGHT = newHeight;}
void setRacketVel(Racket tmp, float newVel){tmp->RACKET_VEL = newVel;}