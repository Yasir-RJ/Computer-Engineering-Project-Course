#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

#include "arena.h"
#include "defs.h"

struct arena
{
    SDL_Rect NWcorner;
    SDL_Rect NEcorner;
    SDL_Rect SEcorner;
    SDL_Rect SWcorner;

    SDL_Rect CNWcorner;
    SDL_Rect CNEcorner;
    SDL_Rect CSEcorner;
    SDL_Rect CSWcorner;

    SDL_Texture *TILE_TEXTURE;
};

Arena arenaCreate(int arenaNr, SDL_Renderer *gRenderer)
{
    Arena tmp = malloc(sizeof(struct arena));
    SDL_Surface *tmpSurface = SDL_LoadBMP("tile.bmp");
    tmp->TILE_TEXTURE = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);

    if(arenaNr == 1)
    {
        tmp->NWcorner.x = SCREEN_WIDTH - SCREEN_WIDTH;
        tmp->NWcorner.y = SCREEN_HEIGHT - SCREEN_HEIGHT;
        tmp->NWcorner.w = SCREEN_WIDTH * 0.25;
        tmp->NWcorner.h = SCREEN_HEIGHT * 0.25;

        tmp->NEcorner.x = SCREEN_WIDTH * 0.75;
        tmp->NEcorner.y = SCREEN_HEIGHT - SCREEN_HEIGHT;
        tmp->NEcorner.w = SCREEN_WIDTH * 0.25;
        tmp->NEcorner.h = SCREEN_HEIGHT * 0.25;

        tmp->SEcorner.x = SCREEN_WIDTH * 0.75;
        tmp->SEcorner.y = SCREEN_HEIGHT * 0.75;
        tmp->SEcorner.w = SCREEN_WIDTH * 0.25;
        tmp->SEcorner.h = SCREEN_HEIGHT * 0.25;

        tmp->SWcorner.x = SCREEN_WIDTH - SCREEN_WIDTH;
        tmp->SWcorner.y = SCREEN_HEIGHT * 0.75;
        tmp->SWcorner.w = SCREEN_WIDTH * 0.25;
        tmp->SWcorner.h = SCREEN_HEIGHT * 0.25;

        tmp->CNWcorner.x = 0;
        tmp->CNWcorner.y = 0;
        tmp->CNWcorner.w = 0;
        tmp->CNWcorner.h = 0;

        tmp->CNEcorner.x = 0;
        tmp->CNEcorner.y = 0;
        tmp->CNEcorner.w = 0;
        tmp->CNEcorner.h = 0;

        tmp->CSEcorner.x = 0;
        tmp->CSEcorner.y = 0;
        tmp->CSEcorner.w = 0;
        tmp->CSEcorner.h = 0;

        tmp->CSWcorner.x = 0;
        tmp->CSWcorner.y = 0;
        tmp->CSWcorner.w = 0;
        tmp->CSWcorner.h = 0;
    }

    else if(arenaNr == 2)
    { 
        tmp->NWcorner.x = SCREEN_WIDTH - SCREEN_WIDTH;
        tmp->NWcorner.y = SCREEN_HEIGHT - SCREEN_HEIGHT;
        tmp->NWcorner.w = SCREEN_WIDTH * 0.20;
        tmp->NWcorner.h = SCREEN_HEIGHT * 0.20;

        tmp->NEcorner.x = SCREEN_WIDTH * 0.80;
        tmp->NEcorner.y = SCREEN_HEIGHT - SCREEN_HEIGHT;
        tmp->NEcorner.w = SCREEN_WIDTH * 0.20;
        tmp->NEcorner.h = SCREEN_HEIGHT * 0.20;

        tmp->SEcorner.x = SCREEN_WIDTH * 0.80;
        tmp->SEcorner.y = SCREEN_HEIGHT * 0.80;
        tmp->SEcorner.w = SCREEN_WIDTH * 0.20;
        tmp->SEcorner.h = SCREEN_HEIGHT * 0.20;

        tmp->SWcorner.x = SCREEN_WIDTH - SCREEN_WIDTH;
        tmp->SWcorner.y = SCREEN_HEIGHT * 0.80;
        tmp->SWcorner.w = SCREEN_WIDTH * 0.20;
        tmp->SWcorner.h = SCREEN_HEIGHT * 0.20;

        tmp->CNWcorner.x = SCREEN_WIDTH * 0.30;
        tmp->CNWcorner.y = SCREEN_HEIGHT * 0.30;
        tmp->CNWcorner.w = SCREEN_WIDTH * 0.15;
        tmp->CNWcorner.h = SCREEN_HEIGHT * 0.15;

        tmp->CNEcorner.x = SCREEN_WIDTH * 0.55;
        tmp->CNEcorner.y = SCREEN_HEIGHT * 0.30;
        tmp->CNEcorner.w = SCREEN_WIDTH * 0.15;
        tmp->CNEcorner.h = SCREEN_HEIGHT * 0.15;

        tmp->CSEcorner.x = SCREEN_WIDTH * 0.55;
        tmp->CSEcorner.y = SCREEN_HEIGHT * 0.55;
        tmp->CSEcorner.w = SCREEN_WIDTH * 0.15;
        tmp->CSEcorner.h = SCREEN_HEIGHT * 0.15;

        tmp->CSWcorner.x = SCREEN_WIDTH * 0.30;
        tmp->CSWcorner.y = SCREEN_HEIGHT * 0.55;
        tmp->CSWcorner.w = SCREEN_WIDTH * 0.15;
        tmp->CSWcorner.h = SCREEN_WIDTH * 0.15;
    }

    else if(arenaNr == 3)
    { 
        tmp->NWcorner.x = SCREEN_WIDTH - SCREEN_WIDTH;
        tmp->NWcorner.y = SCREEN_HEIGHT - SCREEN_HEIGHT;
        tmp->NWcorner.w = SCREEN_WIDTH * 0.35;
        tmp->NWcorner.h = SCREEN_HEIGHT * 0.35;

        tmp->NEcorner.x = SCREEN_WIDTH * 0.65;
        tmp->NEcorner.y = SCREEN_HEIGHT - SCREEN_HEIGHT;
        tmp->NEcorner.w = SCREEN_WIDTH * 0.35;
        tmp->NEcorner.h = SCREEN_HEIGHT * 0.35;

        tmp->SEcorner.x = SCREEN_WIDTH * 0.65;
        tmp->SEcorner.y = SCREEN_HEIGHT * 0.65;
        tmp->SEcorner.w = SCREEN_WIDTH * 0.35;
        tmp->SEcorner.h = SCREEN_HEIGHT * 0.35;

        tmp->SWcorner.x = SCREEN_WIDTH - SCREEN_WIDTH;
        tmp->SWcorner.y = SCREEN_HEIGHT * 0.65;
        tmp->SWcorner.w = SCREEN_WIDTH * 0.35;
        tmp->SWcorner.h = SCREEN_HEIGHT * 0.35;

        tmp->CNWcorner.x = SCREEN_WIDTH * 0.45;
        tmp->CNWcorner.y = SCREEN_HEIGHT * 0.30;
        tmp->CNWcorner.w = SCREEN_WIDTH * 0.10;
        tmp->CNWcorner.h = SCREEN_HEIGHT * 0.05;

        tmp->CNEcorner.x = SCREEN_WIDTH * 0.65;
        tmp->CNEcorner.y = SCREEN_HEIGHT * 0.45;
        tmp->CNEcorner.w = SCREEN_WIDTH * 0.05;
        tmp->CNEcorner.h = SCREEN_HEIGHT * 0.10;

        tmp->CSEcorner.x = SCREEN_WIDTH * 0.30;
        tmp->CSEcorner.y = SCREEN_HEIGHT * 0.45;
        tmp->CSEcorner.w = SCREEN_WIDTH * 0.05;
        tmp->CSEcorner.h = SCREEN_HEIGHT * 0.10;

        tmp->CSWcorner.x = SCREEN_WIDTH * 0.45;
        tmp->CSWcorner.y = SCREEN_HEIGHT * 0.65;
        tmp->CSWcorner.w = SCREEN_WIDTH * 0.10;
        tmp->CSWcorner.h = SCREEN_HEIGHT * 0.05;
    }

    tmpSurface = NULL;

    return tmp;
}

void arenaRender(Arena tmp, SDL_Renderer *gRenderer)
{
    SDL_RenderCopyEx(gRenderer, tmp->TILE_TEXTURE, NULL, &tmp->NWcorner, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer, tmp->TILE_TEXTURE, NULL, &tmp->NEcorner, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer, tmp->TILE_TEXTURE, NULL, &tmp->SEcorner, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer, tmp->TILE_TEXTURE, NULL, &tmp->SWcorner, 0, NULL, SDL_FLIP_NONE);

    SDL_RenderCopyEx(gRenderer, tmp->TILE_TEXTURE, NULL, &tmp->CNWcorner, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer, tmp->TILE_TEXTURE, NULL, &tmp->CNEcorner, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer, tmp->TILE_TEXTURE, NULL, &tmp->CSEcorner, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer, tmp->TILE_TEXTURE, NULL, &tmp->CSWcorner, 0, NULL, SDL_FLIP_NONE);

    return;
}

SDL_Rect *getArenaNWCorner(Arena tmp) {return &tmp->NWcorner;}
SDL_Rect *getArenaNECorner(Arena tmp) {return &tmp->NEcorner;}
SDL_Rect *getArenaSECorner(Arena tmp) {return &tmp->SEcorner;}
SDL_Rect *getArenaSWCorner(Arena tmp) {return &tmp->SWcorner;}
void destroyArena(Arena tmp) {SDL_free(tmp);}

// SERVER ARENA

struct serverArena
{
    SDL_Rect NWcorner;
    SDL_Rect NEcorner;
    SDL_Rect SEcorner;
    SDL_Rect SWcorner;

    SDL_Rect CNWcorner;
    SDL_Rect CNEcorner;
    SDL_Rect CSEcorner;
    SDL_Rect CSWcorner;
};

ServerArena serverArenaCreate(int arenaNr)
{
    ServerArena tmp = malloc(sizeof(struct arena));

    if(arenaNr == 1)
    { 
        tmp->NWcorner.x = SCREEN_WIDTH - SCREEN_WIDTH;
        tmp->NWcorner.y = SCREEN_HEIGHT - SCREEN_HEIGHT;
        tmp->NWcorner.w = SCREEN_WIDTH * 0.25;
        tmp->NWcorner.h = SCREEN_HEIGHT * 0.25;

        tmp->NEcorner.x = SCREEN_WIDTH * 0.75;
        tmp->NEcorner.y = SCREEN_HEIGHT - SCREEN_HEIGHT;
        tmp->NEcorner.w = SCREEN_WIDTH * 0.25;
        tmp->NEcorner.h = SCREEN_HEIGHT * 0.25;

        tmp->SEcorner.x = SCREEN_WIDTH * 0.75;
        tmp->SEcorner.y = SCREEN_HEIGHT * 0.75;
        tmp->SEcorner.w = SCREEN_WIDTH * 0.25;
        tmp->SEcorner.h = SCREEN_HEIGHT * 0.25;

        tmp->SWcorner.x = SCREEN_WIDTH - SCREEN_WIDTH;
        tmp->SWcorner.y = SCREEN_HEIGHT * 0.75;
        tmp->SWcorner.w = SCREEN_WIDTH * 0.25;
        tmp->SWcorner.h = SCREEN_HEIGHT * 0.25;

        tmp->CNWcorner.x = 0;
        tmp->CNWcorner.y = 0;
        tmp->CNWcorner.w = 0;
        tmp->CNWcorner.h = 0;

        tmp->CNEcorner.x = 0;
        tmp->CNEcorner.y = 0;
        tmp->CNEcorner.w = 0;
        tmp->CNEcorner.h = 0;

        tmp->CSEcorner.x = 0;
        tmp->CSEcorner.y = 0;
        tmp->CSEcorner.w = 0;
        tmp->CSEcorner.h = 0;

        tmp->CSWcorner.x = 0;
        tmp->CSWcorner.y = 0;
        tmp->CSWcorner.w = 0;
        tmp->CSWcorner.h = 0;
    }

    else if(arenaNr == 2)
    { 
        tmp->NWcorner.x = SCREEN_WIDTH - SCREEN_WIDTH;
        tmp->NWcorner.y = SCREEN_HEIGHT - SCREEN_HEIGHT;
        tmp->NWcorner.w = SCREEN_WIDTH * 0.20;
        tmp->NWcorner.h = SCREEN_HEIGHT * 0.20;

        tmp->NEcorner.x = SCREEN_WIDTH * 0.80;
        tmp->NEcorner.y = SCREEN_HEIGHT - SCREEN_HEIGHT;
        tmp->NEcorner.w = SCREEN_WIDTH * 0.20;
        tmp->NEcorner.h = SCREEN_HEIGHT * 0.20;

        tmp->SEcorner.x = SCREEN_WIDTH * 0.80;
        tmp->SEcorner.y = SCREEN_HEIGHT * 0.80;
        tmp->SEcorner.w = SCREEN_WIDTH * 0.20;
        tmp->SEcorner.h = SCREEN_HEIGHT * 0.20;

        tmp->SWcorner.x = SCREEN_WIDTH - SCREEN_WIDTH;
        tmp->SWcorner.y = SCREEN_HEIGHT * 0.80;
        tmp->SWcorner.w = SCREEN_WIDTH * 0.20;
        tmp->SWcorner.h = SCREEN_HEIGHT * 0.20;

        tmp->CNWcorner.x = SCREEN_WIDTH * 0.30;
        tmp->CNWcorner.y = SCREEN_HEIGHT * 0.30;
        tmp->CNWcorner.w = SCREEN_WIDTH * 0.15;
        tmp->CNWcorner.h = SCREEN_HEIGHT * 0.15;

        tmp->CNEcorner.x = SCREEN_WIDTH * 0.55;
        tmp->CNEcorner.y = SCREEN_HEIGHT * 0.30;
        tmp->CNEcorner.w = SCREEN_WIDTH * 0.15;
        tmp->CNEcorner.h = SCREEN_HEIGHT * 0.15;

        tmp->CSEcorner.x = SCREEN_WIDTH * 0.55;
        tmp->CSEcorner.y = SCREEN_HEIGHT * 0.55;
        tmp->CSEcorner.w = SCREEN_WIDTH * 0.15;
        tmp->CSEcorner.h = SCREEN_HEIGHT * 0.15;

        tmp->CSWcorner.x = SCREEN_WIDTH * 0.30;
        tmp->CSWcorner.y = SCREEN_HEIGHT * 0.55;
        tmp->CSWcorner.w = SCREEN_WIDTH * 0.15;
        tmp->CSWcorner.h = SCREEN_WIDTH * 0.15;
    }

    else if(arenaNr == 3)
    { 
        tmp->NWcorner.x = SCREEN_WIDTH - SCREEN_WIDTH;
        tmp->NWcorner.y = SCREEN_HEIGHT - SCREEN_HEIGHT;
        tmp->NWcorner.w = SCREEN_WIDTH * 0.35;
        tmp->NWcorner.h = SCREEN_HEIGHT * 0.35;

        tmp->NEcorner.x = SCREEN_WIDTH * 0.65;
        tmp->NEcorner.y = SCREEN_HEIGHT - SCREEN_HEIGHT;
        tmp->NEcorner.w = SCREEN_WIDTH * 0.35;
        tmp->NEcorner.h = SCREEN_HEIGHT * 0.35;

        tmp->SEcorner.x = SCREEN_WIDTH * 0.65;
        tmp->SEcorner.y = SCREEN_HEIGHT * 0.65;
        tmp->SEcorner.w = SCREEN_WIDTH * 0.35;
        tmp->SEcorner.h = SCREEN_HEIGHT * 0.35;

        tmp->SWcorner.x = SCREEN_WIDTH - SCREEN_WIDTH;
        tmp->SWcorner.y = SCREEN_HEIGHT * 0.65;
        tmp->SWcorner.w = SCREEN_WIDTH * 0.35;
        tmp->SWcorner.h = SCREEN_HEIGHT * 0.35;

        tmp->CNWcorner.x = SCREEN_WIDTH * 0.45;
        tmp->CNWcorner.y = SCREEN_HEIGHT * 0.30;
        tmp->CNWcorner.w = SCREEN_WIDTH * 0.10;
        tmp->CNWcorner.h = SCREEN_HEIGHT * 0.05;

        tmp->CNEcorner.x = SCREEN_WIDTH * 0.65;
        tmp->CNEcorner.y = SCREEN_HEIGHT * 0.45;
        tmp->CNEcorner.w = SCREEN_WIDTH * 0.05;
        tmp->CNEcorner.h = SCREEN_HEIGHT * 0.10;

        tmp->CSEcorner.x = SCREEN_WIDTH * 0.30;
        tmp->CSEcorner.y = SCREEN_HEIGHT * 0.45;
        tmp->CSEcorner.w = SCREEN_WIDTH * 0.05;
        tmp->CSEcorner.h = SCREEN_HEIGHT * 0.10;

        tmp->CSWcorner.x = SCREEN_WIDTH * 0.45;
        tmp->CSWcorner.y = SCREEN_HEIGHT * 0.65;
        tmp->CSWcorner.w = SCREEN_WIDTH * 0.10;
        tmp->CSWcorner.h = SCREEN_HEIGHT * 0.05;
    }

    return tmp;
}

SDL_Rect *getServerArenaNWCorner(ServerArena tmp) {return &tmp->NWcorner;}
SDL_Rect *getServerArenaNECorner(ServerArena tmp) {return &tmp->NEcorner;}
SDL_Rect *getServerArenaSECorner(ServerArena tmp) {return &tmp->SEcorner;}
SDL_Rect *getServerArenaSWCorner(ServerArena tmp) {return &tmp->SWcorner;}

SDL_Rect *getServerArenaCNWCorner(ServerArena tmp) {return &tmp->CNWcorner;}
SDL_Rect *getServerArenaCNECorner(ServerArena tmp) {return &tmp->CNEcorner;}
SDL_Rect *getServerArenaCSECorner(ServerArena tmp) {return &tmp->CSEcorner;}
SDL_Rect *getServerArenaCSWCorner(ServerArena tmp) {return &tmp->CSWcorner;}

void destroyServerArena(ServerArena tmp) {SDL_free(tmp);}
