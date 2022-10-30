#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>
#include <SDL_net.h>
#include <SDL_image.h>

#include "racket.h"
#include "arena.h"
#include "defs.h"
#include "Score.h"
#include "Audio.h"

typedef struct
{
    int playerNr;
    int arenaNr;
} dataStructConnection;

typedef struct
{
    int racketXPos[MAX_CLIENT];
    int ballxPos[MAX_BALL];
    int ballyPos[MAX_BALL];
    int playerScore[MAX_CLIENT];
    int activeBalls;
    bool playSound[MAX_SOUND];
    bool running;
} dataStructRecieve;

typedef struct
{
    int racketXPos;
} dataStructSend;

UDPsocket serverSocket;
IPaddress serverIP;

UDPpacket *sendPacket;
UDPpacket *recievePacket;

dataStructSend UDPdataSend = {352};
dataStructRecieve UDPdataRecieve = {{352, 352, 352, 352}, {376, 0, 0}, {376, 0, 0}, {0, 0, 0, 0}, 0, {false, false}, true};
dataStructConnection UDPdataConnect = {-1, -1};

void networkGetPlayerNr()
{
    sendPacket->len = sizeof(dataStructConnection) + 1;
    sendPacket->address.host = serverIP.host;
    sendPacket->address.port = serverIP.port;
    memcpy((char *) sendPacket->data, &UDPdataConnect, sizeof(dataStructConnection) + 1);

    while(UDPdataConnect.arenaNr < 0 || UDPdataConnect.playerNr < 0)
    {
        SDLNet_UDP_Send(serverSocket, -1, sendPacket);
        if(SDLNet_UDP_Recv(serverSocket, recievePacket))
        {
            memcpy(&UDPdataConnect, (char *) recievePacket->data, sizeof(dataStructConnection));
            fprintf(stderr, "Client %d %d\n", UDPdataConnect.playerNr, UDPdataConnect.arenaNr);
        }
    }

    return;
}

void application(char *IPadd)
{
    bool running = true;

    SDL_Renderer *gRenderer = NULL;
    SDL_Window *gWindow = NULL;
    SDL_Surface *gSurface = NULL;
    SDL_Event gEvent;

    Score score = (Score) malloc(sizeof(Score));
    Audio audio = (Audio) malloc(sizeof(Audio));

    SDLNet_Init();

    serverSocket = SDLNet_UDP_Open(0);
    sendPacket = SDLNet_AllocPacket(256);
    recievePacket = SDLNet_AllocPacket(256);
    SDLNet_ResolveHost(&serverIP, IPadd, 2000);

    networkGetPlayerNr();

    gWindow = SDL_CreateWindow("PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(gRenderer, 0x20, 0x20, 0x20, 0xFF);

    Racket racket[MAX_CLIENT];
    for(int i = 0; i < MAX_CLIENT; i++)
        racket[i] = racketCreate(i, gRenderer);

    Arena arena = arenaCreate(UDPdataConnect.arenaNr, gRenderer);
    SDL_Rect rectBall[MAX_BALL] = {{0, 0, 12, 12}, {0, 0, 12, 12}, {0, 0, 12, 12}, {0, 0, 24, 24}};

    bool racketKeyLeft = false;
    bool racketKeyRight = false;
    
    SDL_Surface *tmpSurface = IMG_Load("ball.png");
    SDL_Texture *tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    if(!InitTTF(gRenderer, score))
        fprintf(stderr, "Failure\n");

    if(!InitAudio(audio))
        fprintf(stderr, "Failure\n");

    //PlayMusic(audio);

    while(running)
    {
        // RENDERER
        SDL_RenderClear(gRenderer);
        racketRender(UDPdataConnect.playerNr, racket, gRenderer);
        arenaRender(arena, gRenderer);
        for(int i = 0; i < UDPdataRecieve.activeBalls; i++)
            SDL_RenderCopy(gRenderer, tmpTexture, NULL, &rectBall[i]);
        RenderScore(gRenderer, score);
        SDL_RenderPresent(gRenderer);

        while(SDL_PollEvent(&gEvent) != 0)
        {
            if(gEvent.type == SDL_QUIT)
                running = false;

            else if(gEvent.type == SDL_KEYUP)
            {
                if(gEvent.key.keysym.sym == SDLK_LEFT)
                    racketKeyLeft = 0;

                if(gEvent.key.keysym.sym == SDLK_RIGHT)
                    racketKeyRight = 0;
            }

            else if(gEvent.type == SDL_KEYDOWN)
            {
                if(gEvent.key.keysym.sym == SDLK_LEFT)
                    racketKeyLeft = 1;

                if(gEvent.key.keysym.sym == SDLK_RIGHT)
                    racketKeyRight = 1;
            }
        }

        racket[0] = racketUpdate(racket[0], racketKeyLeft, racketKeyRight, arena);

        if(UDPdataSend.racketXPos != getRacketPosX(racket[0]))
        {
            UDPdataSend.racketXPos = getRacketPosX(racket[0]);
            memcpy((char *) sendPacket->data, &UDPdataSend, sizeof(dataStructRecieve));
            sendPacket->len = sizeof(dataStructRecieve) + 1;
            sendPacket->address.host = serverIP.host;
            sendPacket->address.port = serverIP.port;
            SDLNet_UDP_Send(serverSocket, -1, sendPacket);
        }

        if(SDLNet_UDP_Recv(serverSocket, recievePacket))
        {
            memcpy(&UDPdataRecieve, (char *) recievePacket->data, sizeof(dataStructRecieve));

            SetPlayerScore(UDPdataRecieve.playerScore, score, UDPdataConnect.playerNr);

            if(UDPdataRecieve.playSound[0])
            {
                PlayWallSound(audio);
                UDPdataRecieve.playSound[0] = false;
            }

            if(UDPdataRecieve.playSound[1])
            {
                PlayRacketSound(audio);
                UDPdataRecieve.playSound[1] = false;
            }

            if(UDPdataConnect.playerNr == 0)       // RED RACKET PERSPECTIVE
            {
                setRacketPosX(racket[1], SCREEN_WIDTH - getRacketWidth(racket[1]) - UDPdataRecieve.racketXPos[1]);
                setRacketPosY(racket[2], (getRacketWidth(racket[2]) / 2) + UDPdataRecieve.racketXPos[2]);
                setRacketPosY(racket[3], SCREEN_HEIGHT - (getRacketWidth(racket[3]) / 2) - UDPdataRecieve.racketXPos[3]);

                for(int i = 0; i < UDPdataRecieve.activeBalls; i++)
                {
                    rectBall[i].x = UDPdataRecieve.ballxPos[i];
                    rectBall[i].y = UDPdataRecieve.ballyPos[i];
                }
            }

            else if(UDPdataConnect.playerNr == 1)      // GREEN RACKET PERSPECTIVE
            {
                setRacketPosX(racket[1], SCREEN_WIDTH - getRacketWidth(racket[1]) - UDPdataRecieve.racketXPos[0]);
                setRacketPosY(racket[3], SCREEN_HEIGHT - (getRacketWidth(racket[3]) / 2) - UDPdataRecieve.racketXPos[2]);
                setRacketPosY(racket[2], (getRacketWidth(racket[2]) / 2) + UDPdataRecieve.racketXPos[3]);

                for(int i = 0; i < UDPdataRecieve.activeBalls; i++)
                {
                    rectBall[i].x = SCREEN_WIDTH - rectBall[i].w - UDPdataRecieve.ballxPos[i];
                    rectBall[i].y = SCREEN_HEIGHT - rectBall[i].w - UDPdataRecieve.ballyPos[i];
                }
            }

            else if(UDPdataConnect.playerNr == 2)      // BLUE RACKET PERSPECTIVE
            {
                setRacketPosY(racket[3], SCREEN_HEIGHT - (getRacketWidth(racket[3]) / 2) - UDPdataRecieve.racketXPos[0]);
                setRacketPosY(racket[2], (getRacketWidth(racket[3]) / 2) + UDPdataRecieve.racketXPos[1]);
                setRacketPosX(racket[1], SCREEN_WIDTH - getRacketWidth(racket[1]) - UDPdataRecieve.racketXPos[3]);

                for(int i = 0; i < UDPdataRecieve.activeBalls; i++)
                {
                    rectBall[i].x = UDPdataRecieve.ballyPos[i];
                    rectBall[i].y = SCREEN_HEIGHT - rectBall[i].w - UDPdataRecieve.ballxPos[i];
                }
            }

            else if(UDPdataConnect.playerNr == 3)      // YELLOW RACKET PERSPECTIVE
            {
                setRacketPosY(racket[2], (getRacketWidth(racket[2]) / 2) + UDPdataRecieve.racketXPos[0]);
                setRacketPosY(racket[3], SCREEN_HEIGHT - (getRacketWidth(racket[3]) / 2) - UDPdataRecieve.racketXPos[1]);
                setRacketPosX(racket[1], SCREEN_WIDTH - getRacketWidth(racket[1]) - UDPdataRecieve.racketXPos[2]);

                for(int i = 0; i < UDPdataRecieve.activeBalls; i++)
                {
                    rectBall[i].x = SCREEN_WIDTH - rectBall[i].w - UDPdataRecieve.ballyPos[i];
                    rectBall[i].y = UDPdataRecieve.ballxPos[i];
                }
            }
        }

        running = UDPdataRecieve.running;

        SDL_Delay(1000/60);
    }

    SDL_RenderClear(gRenderer);
    RacketRenderFinish(racket, gRenderer, score, UDPdataConnect.playerNr);
    RenderScore(gRenderer, score);
    SDL_RenderPresent(gRenderer);

    SDL_Delay(10000);

    return;
}