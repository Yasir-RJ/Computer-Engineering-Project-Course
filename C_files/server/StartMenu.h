#pragma once

// group 13 ... 13/5/2022  Yasir Riyadh
// needs: back.bmp, Button1.png, Button2.png, music.wav, button.wav

#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#define NumMenu  6

int ShowMenu(SDL_Window* hWnd, SDL_Surface* hSurWnd,int winWidth);