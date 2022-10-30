#ifndef collision_h
#define collision_h

#include "ball.h"
#include "racket.h"
#include "arena.h"

ServerBall checkCollisionBallRacket (ServerBall sBall, SDL_Rect rectRacket[], bool *playSound);
ServerBall checkCollisionBallBorder (ServerBall sBall, int playerScore[]);
ServerBall checkCollisionBallArena (ServerBall sBall, ServerArena sArena, bool *playSound);

#endif