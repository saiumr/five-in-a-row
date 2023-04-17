#ifndef _INIT_H_
#define _INIT_H_

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

extern SDL_Window* window;
extern SDL_Renderer* render;

bool init();
#endif
