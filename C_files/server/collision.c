#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL.h>

#include "collision.h"
#include "ball.h"
#include "racket.h"
#include "arena.h"
#include "defs.h"

ServerBall checkCollisionBallRacket (ServerBall sBall, SDL_Rect rectRacket[], bool *playSound)
{
    for(int i = 0; i < MAX_CLIENT; i++)
    {
        if(SDL_HasIntersection(&rectRacket[i], getServerBallRectHor(sBall)))
        {
            setServerBallVelX(sBall, -(getServerBallVelX(sBall)));
            *playSound = true;
        }
    
        else if(SDL_HasIntersection(&rectRacket[i], getServerBallRectVer(sBall)))
        {
            if(getServerBallVelY(sBall) < 8)
                setServerBallVelY(sBall, -(getServerBallVelY(sBall) + 1));

            else
                setServerBallVelY(sBall, -(getServerBallVelY(sBall)));
            *playSound = true;
        }
    
        else if(SDL_HasIntersection(&rectRacket[i], getServerBallRectDia(sBall)))
        {
            if(getServerBallVelY(sBall) < 8)
                setServerBallVelY(sBall, -(getServerBallVelY(sBall) + 1));

            else
                setServerBallVelY(sBall, -(getServerBallVelY(sBall)));
                
            setServerBallVelX(sBall, -(getServerBallVelX(sBall)));
            *playSound = true;
        }
    }

    //double relative_pos = (racket_x+(racket_width/2) - (ball_x+(ball_radius/2)))/(racket_width/2);

    return sBall;
}

ServerBall checkCollisionBallBorder (ServerBall sBall, int playerScore[])
{
    if(getServerBallPosX(sBall) + getServerBallRadius(sBall) < 0)
    {
        resetBall(sBall);
        playerScore[2]++;
    }

    else if(SCREEN_WIDTH < getServerBallPosX(sBall))
    {
        resetBall(sBall);
        playerScore[3]++;
    }

    else if(getServerBallPosY(sBall) + getServerBallRadius(sBall) < 0)
    {
        resetBall(sBall);
        playerScore[1]++;
    }

    else if(SCREEN_HEIGHT < getServerBallPosY(sBall))
    {
        resetBall(sBall);
        playerScore[0]++;
    }

    return sBall;
}

ServerBall checkCollisionBallArena (ServerBall sBall, ServerArena sArena, bool *playSound)
{
    if(SDL_HasIntersection(getServerArenaNWCorner(sArena), getServerBallRectHor(sBall))
    || SDL_HasIntersection(getServerArenaNECorner(sArena), getServerBallRectHor(sBall))
    || SDL_HasIntersection(getServerArenaSECorner(sArena), getServerBallRectHor(sBall))
    || SDL_HasIntersection(getServerArenaSWCorner(sArena), getServerBallRectHor(sBall))
    || SDL_HasIntersection(getServerArenaCNWCorner(sArena), getServerBallRectHor(sBall))
    || SDL_HasIntersection(getServerArenaCNECorner(sArena), getServerBallRectHor(sBall))
    || SDL_HasIntersection(getServerArenaCSECorner(sArena), getServerBallRectHor(sBall))
    || SDL_HasIntersection(getServerArenaCSWCorner(sArena), getServerBallRectHor(sBall)))
    {
        setServerBallVelX(sBall, -(getServerBallVelX(sBall)));
        *playSound = true;
    }

    else if(SDL_HasIntersection(getServerArenaNWCorner(sArena), getServerBallRectVer(sBall))
    || SDL_HasIntersection(getServerArenaNECorner(sArena), getServerBallRectVer(sBall))
    || SDL_HasIntersection(getServerArenaSECorner(sArena), getServerBallRectVer(sBall))
    || SDL_HasIntersection(getServerArenaSWCorner(sArena), getServerBallRectVer(sBall))
    || SDL_HasIntersection(getServerArenaCNWCorner(sArena), getServerBallRectVer(sBall))
    || SDL_HasIntersection(getServerArenaCNECorner(sArena), getServerBallRectVer(sBall))
    || SDL_HasIntersection(getServerArenaCSECorner(sArena), getServerBallRectVer(sBall))
    || SDL_HasIntersection(getServerArenaCSWCorner(sArena), getServerBallRectVer(sBall)))
    {
        setServerBallVelY(sBall, -(getServerBallVelY(sBall)));
        *playSound = true;
    }

    else if(SDL_HasIntersection(getServerArenaNWCorner(sArena), getServerBallRectDia(sBall))
    || SDL_HasIntersection(getServerArenaNECorner(sArena), getServerBallRectDia(sBall))
    || SDL_HasIntersection(getServerArenaSECorner(sArena), getServerBallRectDia(sBall))
    || SDL_HasIntersection(getServerArenaSWCorner(sArena), getServerBallRectDia(sBall))
    || SDL_HasIntersection(getServerArenaCNWCorner(sArena), getServerBallRectDia(sBall))
    || SDL_HasIntersection(getServerArenaCNECorner(sArena), getServerBallRectDia(sBall))
    || SDL_HasIntersection(getServerArenaCSECorner(sArena), getServerBallRectDia(sBall))
    || SDL_HasIntersection(getServerArenaCSWCorner(sArena), getServerBallRectDia(sBall)))
    {
        setServerBallVelX(sBall, -(getServerBallVelX(sBall)));
        setServerBallVelY(sBall, -(getServerBallVelY(sBall)));
        *playSound = true;
    }

    return sBall;
}