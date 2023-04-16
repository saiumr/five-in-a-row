#ifndef _EVENT_H_
#define _EVENT_H_

#include <SDL2/SDL.h>
#include "port.h"

extern SDL_Event event;
extern bool quit;
void eventHandle(SDL_Event event);

#endif