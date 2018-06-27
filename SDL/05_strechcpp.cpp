#include <SDL.h>
#include <stdio.h>
#include <filesystem>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string path);

enum KeyPressSurface {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gCurrentSurface = NULL;
SDL_Surface* gKeySurfaces[KEY_PRESS_SURFACE_TOTAL];
bool quit = false;
SDL_Event e;

int main(int argc, char* args[]) {
	if (!init()) {
		return 0;
	}
	if (!loadMedia()) {
		return 0;
	}

	gCurrentSurface = gKeySurfaces[KEY_PRESS_SURFACE_DEFAULT];
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				break;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_UP: gCurrentSurface = gKeySurfaces[KEY_PRESS_SURFACE_UP];
					break;

				case SDLK_DOWN: gCurrentSurface = gKeySurfaces[KEY_PRESS_SURFACE_DOWN];
					break;

				case SDLK_LEFT: gCurrentSurface = gKeySurfaces[KEY_PRESS_SURFACE_LEFT];
					break;

				case SDLK_RIGHT: gCurrentSurface = gKeySurfaces[KEY_PRESS_SURFACE_RIGHT];
					break;

				default: gCurrentSurface = gKeySurfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;
				}

			}
		}
		SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
		SDL_UpdateWindowSurface(gWindow);
	}
	close();
	return 0;
}

bool init() {


	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("THere is an error in initialization of SDL: %s\n", SDL_GetError());
		SDL_Delay(3000);
		return false;
	}

	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL) {
		printf("Window initialization failure: %s\n", SDL_GetError());
		SDL_Delay(3000);
		return false;
	}
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	return true;
}

bool loadMedia() {

	gKeySurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("Resource/press.bmp");
	if (gKeySurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		return false;
	} //Load up surface 
	gKeySurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("Resource/up.bmp");
	if (gKeySurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
		return false;
	} //Load down surface 
	gKeySurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("Resource/down.bmp");
	if (gKeySurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
		return false;
	} //Load left surface
	gKeySurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("Resource/left.bmp");
	if (gKeySurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
		return false;
	} //Load right surface 
	gKeySurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("Resource/right.bmp");
	if (gKeySurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
		return false;
	}
	return true;
}

void close() {
	//SDL_FreeSurface(gHelloWorld);
	//gHelloWorld = NULL; 

	SDL_DestroyWindow(gWindow);

	SDL_Quit();

}
SDL_Surface* loadSurface(std::string path) {
	SDL_Surface* loadSurface = SDL_LoadBMP(path.c_str());
	if (loadSurface == NULL) {
		printf("failure to load %s\n", path.c_str());
		NULL;
	}
	return loadSurface;
}