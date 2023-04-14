#ifndef _INIT_H
#define _INIT_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

extern SDL_Window* window;
extern SDL_Renderer* render;

bool init();
#endif
