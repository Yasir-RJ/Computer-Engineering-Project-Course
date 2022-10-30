#ifndef racket_h
#define racket_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "arena.h"
#include "Score.h"

typedef struct racket *Racket;

Racket racketCreate(int playerNr, SDL_Renderer *gRenderer);
void racketRender(int playerNr, Racket tmp[], SDL_Renderer *gRenderer);
Racket racketUpdate(Racket tmp, bool racketKeyLeft, bool racketKeyRight, Arena arena);
void RacketRenderFinish(Racket tmp[], SDL_Renderer *gRenderer, Score score, int playerNr);

int getRacketHeight(Racket tmp);
int getRacketWidth(Racket tmp);
int getRacketPosX(Racket tmp);
int getRacketPosY(Racket tmp);
int getRacketVel(Racket tmp);

void setRacketPosX(Racket tmp, int xPos);
void setRacketPosY(Racket tmp, int yPos);
void setRacketWidth(Racket tmp, int newWith);
void setRacketHeight(Racket tmp, int newHeight);
void setRacketVel(Racket tmp, float newVel);

#endif