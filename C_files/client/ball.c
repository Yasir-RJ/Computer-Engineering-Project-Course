#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL.h>
#include <SDL_image.h>

#include "ball.h"
#include "defs.h"

struct serverBall
{
    int BALL_POS_X;
    int BALL_POS_Y;
    int BALL_VEL_X;
    int BALL_VEL_Y;
    int BALL_RADIUS;

    SDL_Rect BALL_RECT_HOR;
    SDL_Rect BALL_RECT_VER;
    SDL_Rect BALL_RECT_DIA;
};

ServerBall createServerBall(int init_ball_pos_x, int init_ball_pos_y, int init_ball_Vx, int init_ball_Vy, int radius)
{
    ServerBall tmp = malloc(sizeof(struct serverBall));

    tmp->BALL_POS_X = init_ball_pos_x;
    tmp->BALL_POS_Y = init_ball_pos_y;
    tmp->BALL_VEL_X = init_ball_Vx;
    tmp->BALL_VEL_Y = init_ball_Vy;
    tmp->BALL_RADIUS = radius;

    tmp->BALL_RECT_HOR.x = tmp->BALL_POS_X;
    tmp->BALL_RECT_HOR.y = tmp->BALL_POS_Y + tmp->BALL_RADIUS * 0.34;
    tmp->BALL_RECT_HOR.w = tmp->BALL_RADIUS;
    tmp->BALL_RECT_HOR.h = tmp->BALL_RADIUS * 0.34;

    tmp->BALL_RECT_VER.x = tmp->BALL_POS_X + tmp->BALL_RADIUS * 0.34;
    tmp->BALL_RECT_VER.y = tmp->BALL_POS_Y;
    tmp->BALL_RECT_VER.w = tmp->BALL_RADIUS * 0.34;
    tmp->BALL_RECT_VER.h = tmp->BALL_RADIUS;

    tmp->BALL_RECT_DIA.x = tmp->BALL_POS_X + tmp->BALL_RADIUS * 0.17;
    tmp->BALL_RECT_DIA.y = tmp->BALL_POS_Y + tmp->BALL_RADIUS * 0.17;
    tmp->BALL_RECT_DIA.w = tmp->BALL_RADIUS * 0.67;
    tmp->BALL_RECT_DIA.h = tmp->BALL_RADIUS * 0.67;

    return tmp;
}

void updateServerBall(ServerBall tmp)
{
    tmp->BALL_POS_X += tmp->BALL_VEL_X;
    tmp->BALL_POS_Y += tmp->BALL_VEL_Y;

    tmp->BALL_RECT_HOR.x = tmp->BALL_POS_X;
    tmp->BALL_RECT_HOR.y = tmp->BALL_POS_Y + tmp->BALL_RADIUS * 0.34;

    tmp->BALL_RECT_VER.x = tmp->BALL_POS_X + tmp->BALL_RADIUS * 0.34;
    tmp->BALL_RECT_VER.y = tmp->BALL_POS_Y;

    tmp->BALL_RECT_DIA.x = tmp->BALL_POS_X + tmp->BALL_RADIUS * 0.17;
    tmp->BALL_RECT_DIA.y = tmp->BALL_POS_Y + tmp->BALL_RADIUS * 0.17;
}

void resetBall(ServerBall tmp)
{
    int xVel, yVel;
    randomDir(&xVel, &yVel);

    tmp->BALL_POS_X = (SCREEN_WIDTH - tmp->BALL_RADIUS) / 2;
    tmp->BALL_POS_Y = (SCREEN_HEIGHT - tmp->BALL_RADIUS) / 2;

    tmp->BALL_RECT_HOR.x = tmp->BALL_POS_X;
    tmp->BALL_RECT_HOR.y = tmp->BALL_POS_Y + tmp->BALL_RADIUS * 0.34;

    tmp->BALL_RECT_VER.x = tmp->BALL_POS_X + tmp->BALL_RADIUS * 0.34;
    tmp->BALL_RECT_VER.y = tmp->BALL_POS_Y;

    tmp->BALL_RECT_DIA.x = tmp->BALL_POS_X + tmp->BALL_RADIUS * 0.17;
    tmp->BALL_RECT_DIA.y = tmp->BALL_POS_Y + tmp->BALL_RADIUS * 0.17;

    tmp->BALL_VEL_X = xVel;
    tmp->BALL_VEL_Y = yVel;
}

void randomDir(int *xVel, int *yVel)
{
    int random = rand()%8;

    if(random == 0)
    {
        *xVel = -1;
        *yVel = -2;
    }

    else if(random == 1)
    {
        *xVel = 1;
        *yVel = -2;
    }

    else if(random == 2)
    {
        *xVel = 2;
        *yVel = -1;
    }

    else if(random == 3)
    {
        *xVel = 2;
        *yVel = 1;
    }

    else if(random == 4)
    {
        *xVel = 1;
        *yVel = 2;
    }

    else if(random == 5)
    {
        *xVel = -1;
        *yVel = 2;
    }

    else if(random == 6)
    {
        *xVel = -2;
        *yVel = 1;
    }

    else if(random == 7)
    {
        *xVel = -2;
        *yVel = -1;
    }

    return;
}

// getters;
int getServerBallPosX(ServerBall tmp){return tmp->BALL_POS_X;}
int getServerBallPosY(ServerBall tmp){return tmp->BALL_POS_Y;}
int getServerBallVelX(ServerBall tmp){return tmp->BALL_VEL_X;}
int getServerBallVelY(ServerBall tmp){return tmp->BALL_VEL_Y;}
int getServerBallRadius(ServerBall tmp){return tmp->BALL_RADIUS;}
SDL_Rect *getServerBallRectHor(ServerBall tmp){return &tmp->BALL_RECT_HOR;}
SDL_Rect *getServerBallRectVer(ServerBall tmp){return &tmp->BALL_RECT_VER;}
SDL_Rect *getServerBallRectDia(ServerBall tmp){return &tmp->BALL_RECT_VER;}

// setters
void setServerBallPosX(ServerBall tmp, int x){tmp->BALL_POS_X = x;}
void setServerBallPosY(ServerBall tmp, int y){tmp->BALL_POS_Y = y;}
void setServerBallVelX(ServerBall tmp, int Vx){tmp->BALL_VEL_X = Vx;}
void setServerBallVelY(ServerBall tmp, int Vy){tmp->BALL_VEL_Y = Vy;}
void setServerBallRadius(ServerBall tmp, int radius){tmp->BALL_RADIUS = radius;}