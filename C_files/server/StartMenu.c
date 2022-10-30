
// group 13 ... 13/5/2022  Yasir Riyadh
// Start menu Task

#include "StartMenu.h"

int ShowMenu(SDL_Window* hWnd, SDL_Surface* hSurWnd, int winWidth) {

	Uint32 time;	
	int x, y, oldButton = NumMenu;
	bool IsSelected[NumMenu] = { false };
	const char* MenuItem[NumMenu] = { "Continue","2 Players","4 Players","Setting","Change Arena","Exit Game" };
	SDL_Surface* hSurMenu[NumMenu] = { NULL }, * hSurBackground = NULL, * hSurButton1 = NULL
		, * hSurButton2 = NULL;	
	TTF_Font* hFont = NULL;
	SDL_Color MenuColor[2] = { {0,0,0,255},{0,0,255,255} };
	SDL_Rect ItemRect[NumMenu];
	SDL_Rect ButtonRect[NumMenu];
	Mix_Music* hMenuMusic = NULL;
	Mix_Chunk* hButtonSound = NULL;	

	if (TTF_Init() == -1) {
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 0;
	}
	hFont = TTF_OpenFont("arial.ttf", 35);
	if (!hFont) {
		printf("Failed the load the font: %s\n", TTF_GetError());
		return 0;
	}

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
	hMenuMusic = Mix_LoadMUS("JohnWick.wav");
	Mix_PlayMusic(hMenuMusic, -1);
	hButtonSound = Mix_LoadWAV("button.wav");
	hSurBackground = SDL_LoadBMP("back.bmp");
	if (!hSurBackground) {
		printf("Unable to load image ! SDL Error: %s\n", SDL_GetError());
		return NumMenu - 1;
	}

	IMG_Init(IMG_INIT_PNG);
	hSurButton1 = IMG_Load("Button1.png");
	if (!hSurButton1) {
		printf("Unable to load image ! SDL Error: %s\n", SDL_GetError());
		return NumMenu - 1;
	}
	hSurButton2 = IMG_Load("Button2.png");
	if (!hSurButton2) {
		printf("Unable to load image ! SDL Error: %s\n", SDL_GetError());
		return NumMenu - 1;
	}

	for (int i = 0;i < NumMenu;i++) {
		hSurMenu[i] = TTF_RenderText_Solid(hFont, MenuItem[i], MenuColor[0]);
		ItemRect[i].x = hSurWnd->clip_rect.w / 2 - hSurMenu[i]->clip_rect.w / 2;
		ItemRect[i].y = 150 + 68 * i;
		ButtonRect[i].x = winWidth / 2 - 130;
		ButtonRect[i].y = 130 + 70 * i;
	}

	char* Title1 = (char*)malloc(30);
	char* Title2 = (char*)malloc(30);
	SDL_strlcpy(Title1, "Server Start Menu", 30);
	SDL_strlcpy(Title2, "(Group 13 ... KTH 2022)", 30);
	SDL_Color Title1Color = { 255,0,0 };
	SDL_Color Title2Color = { 173,255,47 };
	SDL_Rect Title1Rect = { winWidth / 2 - 135,30 };
	SDL_Rect Title2Rect = { winWidth / 2 - 180,65 };
	SDL_Surface* hSurTitle1 = TTF_RenderText_Solid(hFont, Title1, Title1Color);
	SDL_Surface* hSurTitle2 = TTF_RenderText_Solid(hFont, Title2, Title2Color);

	SDL_Event event;
	while (1) {
		time = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				for (int i = 0;i < NumMenu;i++)	SDL_FreeSurface(hSurMenu[i]);
				SDL_FreeSurface(hSurTitle1);
				SDL_FreeSurface(hSurTitle2);
				SDL_FreeSurface(hSurButton1);
				SDL_FreeSurface(hSurButton2);
				Mix_FreeChunk(hButtonSound);
				Mix_HaltMusic();
				Mix_FreeMusic(hMenuMusic);
				return NumMenu - 1;
			case SDL_MOUSEMOTION:
				x = event.motion.x;	y = event.motion.y;
				for (int i = 0;i < NumMenu;i++) {
					if (x >= ItemRect[i].x && x <= ItemRect[i].x + ItemRect[i].w && y >= ItemRect[i].y &&
						y <= ItemRect[i].y + ItemRect[i].h) {

						if (i != oldButton) {
							Mix_PlayChannel(-1, hButtonSound, 0);
							oldButton = i;
						}

						if (!IsSelected[i]) {
							IsSelected[i] = true;
							SDL_FreeSurface(hSurMenu[i]);
							hSurMenu[i] = TTF_RenderText_Solid(hFont, MenuItem[i], MenuColor[1]);
						}
					}
					else if (IsSelected[i]) {
						//Mix_PlayChannel(-1, hButtonSound, 0);
						IsSelected[i] = false;
						SDL_FreeSurface(hSurMenu[i]);
						hSurMenu[i] = TTF_RenderText_Solid(hFont, MenuItem[i], MenuColor[0]);
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;	y = event.button.y;
				for (int i = 0;i < NumMenu;i++)
					if (x >= ItemRect[i].x && x <= ItemRect[i].x + ItemRect[i].w && y >= ItemRect[i].y &&
						y <= ItemRect[i].y + ItemRect[i].h) {
						for (int j = 0;j < NumMenu;j++)	SDL_FreeSurface(hSurMenu[j]);
						SDL_FreeSurface(hSurTitle1);
						SDL_FreeSurface(hSurTitle2);
						SDL_FreeSurface(hSurBackground);
						SDL_FreeSurface(hSurButton1);
						SDL_FreeSurface(hSurButton2);
						Mix_FreeChunk(hButtonSound);
						Mix_HaltMusic();
						Mix_FreeMusic(hMenuMusic);
						return i;
					}
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					for (int i = 0;i < NumMenu;i++)	SDL_FreeSurface(hSurMenu[i]);
					SDL_FreeSurface(hSurTitle1);
					SDL_FreeSurface(hSurTitle2);
					SDL_FreeSurface(hSurBackground);
					SDL_FreeSurface(hSurButton1);
					SDL_FreeSurface(hSurButton2);
					Mix_FreeChunk(hButtonSound);
					Mix_HaltMusic();
					Mix_FreeMusic(hMenuMusic);
					return 0;
				}
				break;
			}
		}
		// Rendering		
		SDL_BlitSurface(hSurBackground, NULL, hSurWnd, NULL);
		for (int i = 0;i < NumMenu;i++) {
			if (IsSelected[i]) SDL_BlitSurface(hSurButton2, NULL, hSurWnd, &ButtonRect[i]);
			else SDL_BlitSurface(hSurButton1, NULL, hSurWnd, &ButtonRect[i]);
			SDL_BlitSurface(hSurMenu[i], NULL, hSurWnd, &ItemRect[i]);
		}
		SDL_BlitSurface(hSurTitle1, NULL, hSurWnd, &Title1Rect);
		SDL_BlitSurface(hSurTitle2, NULL, hSurWnd, &Title2Rect);		
		SDL_UpdateWindowSurface(hWnd);
		if (1000 / 30 > (SDL_GetTicks() - time))
			SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
	}
}



