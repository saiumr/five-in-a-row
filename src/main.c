#include "init.h"
#include "event.h"

int main(int argc, char* argv[]) {
    if (!init()) {
        printf("SYSTEM INIT FAILED!\n");
        goto Exit;
    }

    initPositionTable();
    SDL_RenderClear(render);
    while (!quit) {
        drawPort(PORT_THEME1);  // refresh port
        eventHandle(event);
        SDL_RenderPresent(render);
        SDL_RenderClear(render);
        SDL_Delay(100);
    }
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();

Exit:
    printf("goodbye!\n");
    return 0;
}

