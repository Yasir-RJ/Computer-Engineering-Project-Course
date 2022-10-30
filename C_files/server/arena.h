#ifndef arena_h
#define arena_h

typedef struct arena *Arena;

Arena arenaCreate(int arenaNr, SDL_Renderer *gRenderer);
void arenaRender(Arena tmp, SDL_Renderer *gRenderer);
void arenaDestroy(Arena tmp);

SDL_Rect *getArenaNWCorner(Arena tmp);
SDL_Rect *getArenaNECorner(Arena tmp);
SDL_Rect *getArenaSECorner(Arena tmp);
SDL_Rect *getArenaSWCorner(Arena tmp);

// SERVER ARENA

typedef struct serverArena *ServerArena;

ServerArena serverArenaCreate(int arenaNr);
void serverArenaDestroy(ServerArena tmp);

SDL_Rect *getServerArenaNWCorner(ServerArena tmp);
SDL_Rect *getServerArenaNECorner(ServerArena tmp);
SDL_Rect *getServerArenaSECorner(ServerArena tmp);
SDL_Rect *getServerArenaSWCorner(ServerArena tmp);

SDL_Rect *getServerArenaCNWCorner(ServerArena tmp);
SDL_Rect *getServerArenaCNECorner(ServerArena tmp);
SDL_Rect *getServerArenaCSECorner(ServerArena tmp);
SDL_Rect *getServerArenaCSWCorner(ServerArena tmp);

#endif