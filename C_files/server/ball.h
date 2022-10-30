#ifndef ball_h
#define ball_h

// Server ball

typedef struct serverBall *ServerBall;

ServerBall createServerBall(int init_ball_pos_x, int init_ball_pos_y, int init_ball_Vx, int init_ball_Vy, int radius);
void updateServerBall(ServerBall tmp);
void resetBall(ServerBall tmp);
void randomDir(int *xVel, int *yVel);

// getters;
int getServerBallPosX(ServerBall tmp);
int getServerBallPosY(ServerBall tmp);
int getServerBallVelX(ServerBall tmp);
int getServerBallVelY(ServerBall tmp);
int getServerBallRadius(ServerBall tmp);

SDL_Rect *getServerBallRectVer(ServerBall tmp);
SDL_Rect *getServerBallRectHor(ServerBall tmp);
SDL_Rect *getServerBallRectDia(ServerBall tmp);

// setters
void setServerBallPosX(ServerBall tmp, int x);
void setServerBallPosY(ServerBall tmp, int y);
void setServerBallVelX(ServerBall tmp, int Vx);
void setServerBallVelY(ServerBall tmp, int Vy);
void setServerBallRadius(ServerBall tmp, int radius);

#endif