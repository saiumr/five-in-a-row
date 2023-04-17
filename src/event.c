#include "event.h"

Player player = PLAYER_BLACK;
int chessmanCount = 0;
SDL_Point chessmanPosition;
SDL_Event event;
int mouse_x;
int mouse_y;
bool quit = false;

void eventHandle(SDL_Event event) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
        if (event.type == SDL_MOUSEMOTION) {
            mouse_x = event.motion.x;
            mouse_y = event.motion.y;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            chessmanPosition = portCheckIn(mouse_x, mouse_y, player);
            if (chessmanPosition.x == -1 || chessmanPosition.y == -1) continue;  // outside range
            if (positionStatusTable[chessmanPosition.x][chessmanPosition.y] == PORT_LOCATION_OCCUPIED) continue;  // have been recorded
            ++chessmanCount;
            chessmanStatusTableChange(chessmanPosition.x, chessmanPosition.y, player);

            if (checkWon(player)) {
                printf("Winner is player \"%s\"!\n", player_name[player]);
                quit = true;
            }
            else if (chessmanCount == LINE_NUM * LINE_NUM) {
                printf("No Winner!\n");
                quit = true;
            }
            else {
                player = player == PLAYER_WHITE ? PLAYER_BLACK : PLAYER_WHITE;
            }
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }
        }
    }
    portCheckIn(mouse_x, mouse_y, player);
    if (chessmanCount > 0 ) chessmanLocationView();
}
