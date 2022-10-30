#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_net.h>

#include "ball.h"
#include "arena.h"
#include "collision.h"
#include "defs.h"
#include "StartMenu.h"
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
} dataStructSend;

typedef struct
{
    int racketXPos;
} dataStructRecieve;

void serverQuit(UDPpacket *sendPacket, UDPpacket *recievePacket)
{
	SDLNet_FreePacket(sendPacket);
    SDLNet_FreePacket(recievePacket);
	SDLNet_Quit();
    SDL_Quit();

    return;
}

Audio audio;

int main(int argc, char **argv)
{
    bool running = true;
    int ArenaNum = 1;

    Uint32 clientIP[MAX_CLIENT] = { 0 };
    Uint32 clientPort[MAX_CLIENT] = { 0 };
    UDPsocket serverSocket = { NULL };
    UDPpacket* sendPacket = { NULL }, * recievePacket = { NULL };

    dataStructRecieve UDPdataRecieve = { 352 };
    dataStructSend UDPdataSend = { {352, 352, 352, 352}, {376, 0, 0}, {376, 0, 0}, {0, 0, 0, 0}, 0, {false, false}, true };
    dataStructConnection UDPdataConnect = { 0, -1 };

    // Initilize window server

    SDL_Window* hWnd = NULL;
    SDL_Renderer* hRnd = NULL;
    SDL_Surface* hSurface = NULL, * hSurWnd = NULL;
    SDL_Texture* hTexGround = NULL;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    hWnd = SDL_CreateWindow("Server Start Menu - Project1: Group (13) KTH 2022 ",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        600, 600, 0);
    if (!hWnd) {
        printf("Error creating server window: %s\n", SDL_GetError());
        return 1;
    }
    hSurWnd = SDL_GetWindowSurface(hWnd);
    hRnd = SDL_CreateRenderer(hWnd, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!hRnd) {
        printf("Error creating server renderer: %s\n", SDL_GetError());
        return 1;
    }
    hSurface = SDL_LoadBMP("back.bmp");
    if (!hSurface) {
        printf("Failed to load image at %s: %s\n", "back.bmp", SDL_GetError());
        return 1;
    }
    hTexGround = SDL_CreateTextureFromSurface(hRnd, hSurface);
    SDL_FreeSurface(hSurface);
    if (!hTexGround) {
        printf("Failed to create background Texture: %s\n", SDL_GetError());
        return 1;
    }
    // place of Audio code here
    audio = (Audio)malloc(sizeof(Audio));
    // initialize audio 
    if (!InitAudio(audio)) {
        printf("Failed to Initialize Audio in server\n");
        return 1;
    }

    // place of start menu code here 
    int i = ShowMenu(hWnd, hSurWnd, 600);
    switch (i) {
    case (NumMenu - 1): // Exit Game
        running = false;
        return 0;
    case 0: // continue
        running = true;
        break;
    case 1: // 2 players  not implemented yet      
        running = true;
        break;
    case 2: // 4 players        
        running = true;
        break;
    case 3: // setting not implemented yet        
        break;
    case 4: 
        ArenaNum++;        
        if (ArenaNum == 4) ArenaNum = 1;
        break;
    }

    SDL_MinimizeWindow(hWnd);
    UDPdataConnect.arenaNr = ArenaNum;
        
    srand(time(0));
    //printf("Arena(1/2/3): ");
    //scanf_s(" %d", &UDPdataConnect.arenaNr);

    SDLNet_Init();  // Initiate network API

    serverSocket = SDLNet_UDP_Open(2000);    // Open host socket.
    sendPacket = SDLNet_AllocPacket(256);
    recievePacket = SDLNet_AllocPacket(256);

    
    int ballWait = 180;
    int xVel = 0, yVel = 0;
    int gameFinished = 5400;

    ServerBall sBall[MAX_BALL];
    SDL_Rect rectRacket[MAX_CLIENT] = {{352, 676, 64, 12}, {352, 88, 64, 12}, {88, 380, 12, 64}, {676, 380, 12, 64}};
    ServerArena sArena = serverArenaCreate(UDPdataConnect.arenaNr);

    printf("Waiting for Client(0/4)...\n");

    while(running)
    {
        if(SDLNet_UDP_Recv(serverSocket, recievePacket))
        {
            if(clientIP[0] == 0 && clientPort[0] == 0)
            {
                clientIP[0] = recievePacket->address.host;
                clientPort[0] = recievePacket->address.port;
                sendPacket->address.host = clientIP[0];
                sendPacket->address.port = clientPort[0];
                sendPacket->len = sizeof(dataStructConnection) + 1;

                memcpy((char *) sendPacket->data, &UDPdataConnect, sizeof(dataStructConnection) + 1);
                SDLNet_UDP_Send(serverSocket, -1, sendPacket);
                printf("Client %d: Connected\n", UDPdataConnect.playerNr++);
                printf("Waiting for Client(1/4)...\n");
            }
            
            else if(recievePacket->address.port != clientPort[0] && clientIP[1] == 0)
            {
                clientIP[1] = recievePacket->address.host;
                clientPort[1] = recievePacket->address.port;
                sendPacket->address.host = clientIP[1];
                sendPacket->address.port = clientPort[1];
                sendPacket->len = sizeof(dataStructConnection) + 1;

                memcpy((char *) sendPacket->data, &UDPdataConnect, sizeof(dataStructConnection) + 1);
                SDLNet_UDP_Send(serverSocket, -1, sendPacket);
                printf("Client %d: Connected\n", UDPdataConnect.playerNr++);
                printf("Waiting for Client(2/4)...\n");
            }
            
            else if(recievePacket->address.port != clientPort[0] && recievePacket->address.port != clientPort[1] && clientIP[2] == 0)
            {
                clientIP[2] = recievePacket->address.host;
                clientPort[2] = recievePacket->address.port;
                sendPacket->address.host = clientIP[2];
                sendPacket->address.port = clientPort[2];
                sendPacket->len = sizeof(dataStructConnection) + 1;

                memcpy((char *) sendPacket->data, &UDPdataConnect, sizeof(dataStructConnection) + 1);
                SDLNet_UDP_Send(serverSocket, -1, sendPacket);
                printf("Client %d: Connected\n", UDPdataConnect.playerNr++);
                printf("Waiting for Client(3/4)...\n");
            }

            else if(recievePacket->address.port != clientPort[0] && recievePacket->address.port != clientPort[1] && recievePacket->address.port != clientPort[2] && clientIP[3] == 0)
            {
                clientIP[3] = recievePacket->address.host;
                clientPort[3] = recievePacket->address.port;
                sendPacket->address.host = clientIP[3];
                sendPacket->address.port = clientPort[3];
                sendPacket->len = sizeof(dataStructConnection) + 1;

                memcpy((char *) sendPacket->data, &UDPdataConnect, sizeof(dataStructConnection) + 1);
                SDLNet_UDP_Send(serverSocket, -1, sendPacket);
                printf("Client %d: Connected\n", UDPdataConnect.playerNr++);
            }

            else
            {
                if(clientPort[3] != 0)
                {
                    for(int i = 0; i < MAX_CLIENT; i++)
                    {
                        if(recievePacket->address.port == clientPort[i])
                        {
                            memcpy(&UDPdataRecieve, (char *) recievePacket->data, sizeof(dataStructRecieve));
                            UDPdataSend.racketXPos[i] = UDPdataRecieve.racketXPos;
                        }
                    }
                }
            }
        }

        if(clientPort[3] != 0)
        {
            for(int i = 0; i < MAX_SOUND; i++)
                UDPdataSend.playSound[i] = false;

            for(int i = 0; i < UDPdataSend.activeBalls; i++)
            {
                sBall[i] = checkCollisionBallBorder(sBall[i], UDPdataSend.playerScore);
                sBall[i] = checkCollisionBallRacket(sBall[i], rectRacket, &UDPdataSend.playSound[1]);
                sBall[i] = checkCollisionBallArena(sBall[i], sArena, &UDPdataSend.playSound[0]);
                
                updateServerBall(sBall[i]);

                UDPdataSend.ballxPos[i] = getServerBallPosX(sBall[i]);
                UDPdataSend.ballyPos[i] = getServerBallPosY(sBall[i]);
            }

            for(int i = 0; i < MAX_CLIENT; i++)
            {
                if(i == 0)
                    rectRacket[i].x = UDPdataSend.racketXPos[i];

                else if(i == 1)
                    rectRacket[i].x = SCREEN_WIDTH - 64 - UDPdataSend.racketXPos[i];
                
                else if(i == 2)
                    rectRacket[i].y = UDPdataSend.racketXPos[i];

                else if(i == 3)
                    rectRacket[i].y = SCREEN_HEIGHT - 64 - UDPdataSend.racketXPos[i];
            }

            if(ballWait-- < 0 && UDPdataSend.activeBalls != 4)
            {
                randomDir(&xVel, &yVel);

                if(UDPdataSend.activeBalls < 3)
                    sBall[UDPdataSend.activeBalls] = createServerBall((SCREEN_WIDTH - 12) / 2, (SCREEN_HEIGHT - 12) / 2, xVel, yVel, 12);

                else if(UDPdataSend.activeBalls == 3)
                    sBall[UDPdataSend.activeBalls] = createServerBall((SCREEN_WIDTH - 24) / 2, (SCREEN_HEIGHT - 24) / 2, xVel, yVel, 24);

                UDPdataSend.activeBalls++;
                ballWait = 900;
            }

            for(int i = 0; i < MAX_CLIENT; i++)
            {
                if(clientIP[i] != 0 && clientPort[i] != 0)
                {
                    sendPacket->address.host = clientIP[i];
                    sendPacket->address.port = clientPort[i];
                    memcpy((char *) sendPacket->data, &UDPdataSend, sizeof(dataStructSend) + 1);
                    sendPacket->len = sizeof(dataStructSend) + 1;
                    SDLNet_UDP_Send(serverSocket, -1, sendPacket);
                }
            }

            if(gameFinished-- < 0)
                UDPdataSend.running = false;

            SDL_Delay(1000/60);     // Server refresh rate
        }
    }

    serverQuit(sendPacket, recievePacket);
    return 0;
}