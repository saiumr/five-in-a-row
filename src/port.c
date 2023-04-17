#include "port.h"
#include "DrawCircle.h"

SDL_Point portPositionTable[LINE_NUM][LINE_NUM];
Port_Location positionStatusTable[LINE_NUM][LINE_NUM];
Chessman_Status chessmanStatusTable[LINE_NUM * LINE_NUM];
SDL_Rect portPositionTableCheckRect[LINE_NUM][LINE_NUM];
char player_name[2][16] = {"BLACK", "WHITE"};

/**
 * \brief Get point or rect table subscript.
 * \param x The mouse x coordinate.
 * \param y The mouse y coordinate.
 * \return SDL_Point A point.
 */
SDL_Point getSubscript(int x, int y);

/**
 * \brief Get a position of chessman.
 * \param sub_x The first subscript of portPositionTable Table.
 * \param sub_y The second subscript of portPositionTable Table.
 * \return SDL_Point coordinate of point.
 */
SDL_Point getPortPoint(int sub_x, int sub_y);

/**
 * \brief Preview where chess will location.
 * \param x The x coordinate of circle center.
 * \param y The y coordinate of circle center.
 * \param kind 1 Filled or 0 not.
 * \param player PLAYER_BLACK and PLAYER_WHITE
 */
void chessView(int x, int y, int kind, int player);

/**
 * 
 * \brief Change render drawColor.
 * \param render The renderer.
 * \param n The different color. 0 black  1 white 2 green  3 theme0 color  4 theme1 color
 * \param alpha Alpha should be between 0-255.
 */
void portColor(SDL_Renderer* render, Port_Color n, int alpha);


void portColor(SDL_Renderer* render, Port_Color n, int alpha) {
    switch (n) {
    case PORT_COLOR_BLACK:
        SDL_SetRenderDrawColor(render, 0, 0, 0, alpha);  //black
        break;
    case PORT_COLOR_WHITE:
        SDL_SetRenderDrawColor(render, 255, 255, 255, alpha);  //white
        break;
    case PORT_COLOR_GREEN:
        SDL_SetRenderDrawColor(render, 0, 255, 0, alpha);  //green
        break;
    case PORT_COLOR_LIGHT:
        SDL_SetRenderDrawColor(render, 35, 46, 60, alpha);  //theme0 color
        break;
    case PORT_COLOR_DARK:
        SDL_SetRenderDrawColor(render, 231, 182, 145, alpha);  //theme1 color
        break;
    default:
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);  //black
        break;
    }
}

void initPositionTable() {
    int checkRectLength = CHESSMAN_RADIUS * 2;
    int drawCount;
    int posCount;

    for (drawCount = 0; drawCount < LINE_NUM; ++drawCount) {
        for (posCount = 0; posCount < LINE_NUM; ++posCount) {
            int x = (posCount + 1) * LINES_DISTANCE;
            int y = (drawCount + 1) * LINES_DISTANCE;

            portPositionTable[drawCount][posCount].x = x;
            portPositionTable[drawCount][posCount].y = y;

            portPositionTableCheckRect[drawCount][posCount].w = checkRectLength;
            portPositionTableCheckRect[drawCount][posCount].h = checkRectLength;
            portPositionTableCheckRect[drawCount][posCount].x = x - CHESSMAN_RADIUS;
            portPositionTableCheckRect[drawCount][posCount].y = y - CHESSMAN_RADIUS;

            positionStatusTable[drawCount][posCount] = PORT_LOCATION_EMPTY;
            chessmanStatusTable[drawCount * LINE_NUM + posCount].player = PLAYER_ABSENT;
        }
    }

}

void drawPort(Port_Theme theme) {
    SDL_Rect rect = {0, 0, WINDOW_HEIGHT, WINDOW_HEIGHT};
    int d_xy = LINE_NUM * LINES_DISTANCE;
    int drawCount;
    int posCount;
    
    if (theme == PORT_THEME0) {
        portColor(render, PORT_COLOR_DARK, 255);
        SDL_RenderFillRect(render, &rect);
        portColor(render, PORT_COLOR_GREEN, 255);
        // Leave the same size on both sides of the port(chessboard)
        for (drawCount = 0; drawCount < LINE_NUM; ++drawCount) {
            // horizontal line
            SDL_RenderDrawLine(render,
                               LINES_DISTANCE, (drawCount + 1) * LINES_DISTANCE,
                               d_xy, (drawCount + 1) * LINES_DISTANCE);
            // vertical line
            SDL_RenderDrawLine(render,
                               (drawCount + 1) * LINES_DISTANCE, LINES_DISTANCE,
                               (drawCount + 1) * LINES_DISTANCE, d_xy);
        }
        portColor(render, PORT_COLOR_BLACK, 255);
    }
    else if (theme == PORT_THEME1) {
        portColor(render, PORT_COLOR_DARK, 255);
        SDL_RenderFillRect(render, &rect);
        portColor(render, PORT_COLOR_BLACK, 255);
        // Leave the same size on both sides of the port(chessboard)
        for (drawCount = 0; drawCount < LINE_NUM; ++drawCount) {
            SDL_RenderDrawLine(render, LINES_DISTANCE,
                               (drawCount + 1) * LINES_DISTANCE, d_xy,
                               (drawCount + 1) * LINES_DISTANCE);
            SDL_RenderDrawLine(render, (drawCount + 1) * LINES_DISTANCE,
                               LINES_DISTANCE, 
                               (drawCount + 1) * LINES_DISTANCE, d_xy);
        }
    }
}

SDL_Point getSubscript(int x, int y) {
    SDL_Point point;

    // Divide vertically to obtain the number of rows, 
    // and horizontally to obtain the number of columns
    point.x = y / LINES_DISTANCE - 1;
    point.y = x / LINES_DISTANCE - 1;
    if (point.x == -1) point.x = 0;
    if (point.y == -1) point.y = 0;

    return point;
}

SDL_Point getPortPoint(int sub_x, int sub_y) {
    SDL_Point point = {portPositionTable[sub_x][sub_y].x, portPositionTable[sub_x][sub_y].y};
    return point;
}

void chessView(int x, int y, int kind, int player) {
    if (player == PLAYER_WHITE) {
        portColor(render, PORT_COLOR_WHITE, 255);
        drawCircle(render, x, y, CHESSMAN_RADIUS, kind);
        portColor(render, PORT_COLOR_BLACK, 255);    
    }
    else if (player == PLAYER_BLACK) {
        portColor(render, PORT_COLOR_BLACK, 255);
        drawCircle(render, x, y, CHESSMAN_RADIUS, kind);
        portColor(render, PORT_COLOR_BLACK, 255);
    }
}

SDL_Point portCheckIn(int x, int y, Player player) {
    SDL_Point chessLocation;
    // outrange of the port
    if ( (x < LINES_DISTANCE - CHESSMAN_RADIUS) || (x > LINE_NUM * LINES_DISTANCE + CHESSMAN_RADIUS) ||
         (y < LINES_DISTANCE - CHESSMAN_RADIUS) || (y > LINE_NUM * LINES_DISTANCE + CHESSMAN_RADIUS)) {
        chessLocation.x = -1;
        chessLocation.y = -1;
    }
    else {
        SDL_Point point = {x, y};
        SDL_Point point_sub = getSubscript(x, y);

        int pos_x = point_sub.x;
        int pos_y = point_sub.y;
        
        int sub_rx = pos_x + 1;
        int sub_by = pos_y + 1;

        if(SDL_PointInRect(&point, &portPositionTableCheckRect[pos_x][pos_y])) {
            chessView(getPortPoint(pos_x, pos_y).x, getPortPoint(pos_x, pos_y).y, 0, player);
            chessLocation.x = pos_x;
            chessLocation.y = pos_y;
        }
        else if(SDL_PointInRect(&point, &portPositionTableCheckRect[sub_rx][pos_y])) {
            chessView(getPortPoint(sub_rx, pos_y).x, getPortPoint(sub_rx, pos_y).y, 0, player);
            chessLocation.x = sub_rx;
            chessLocation.y = pos_y;
        }
        else if(SDL_PointInRect(&point, &portPositionTableCheckRect[sub_rx][sub_by])) {
            chessView(getPortPoint(sub_rx, sub_by).x, getPortPoint(sub_rx, sub_by).y, 0, player);
            chessLocation.x = sub_rx;
            chessLocation.y = sub_by;
        }
        else if(SDL_PointInRect(&point, &portPositionTableCheckRect[pos_x][sub_by])) {
            chessView(getPortPoint(pos_x, sub_by).x, getPortPoint(pos_x, sub_by).y, 0, player);
            chessLocation.x = pos_x;
            chessLocation.y = sub_by;
        }
        else {
            chessLocation.x = -1;
            chessLocation.y = -1;
        }
    }
    return chessLocation;
}

void chessmanStatusTableChange(int sub_x, int sub_y, Player player) {
    // chessmanStatusTable's index of current chess piece is sub_locatedChessman
    int sub_locatedChessman = sub_x * LINE_NUM + sub_y;

    if (positionStatusTable[sub_x][sub_y] == PORT_LOCATION_EMPTY) {  // there is no chess piece here
        positionStatusTable[sub_x][sub_y] = PORT_LOCATION_OCCUPIED;     // there is a chess piece here now
        chessmanStatusTable[sub_locatedChessman].x = portPositionTable[sub_x][sub_y].x;
        chessmanStatusTable[sub_locatedChessman].y = portPositionTable[sub_x][sub_y].y;
        chessmanStatusTable[sub_locatedChessman].player = player;
    }
}

void chessmanLocationView(int chessmanCount) {
    int sub_statusTable;
    for (size_t row = 0; row < LINE_NUM; ++row) {
        for (size_t column = 0; column < LINE_NUM; ++column) {
            chessView(chessmanStatusTable[row * LINE_NUM + column].x, chessmanStatusTable[row * LINE_NUM + column].y, 1, chessmanStatusTable[row * LINE_NUM + column].player);
        }
    }
}

bool checkWon(Player player) {
    for (size_t row = 0; row < LINE_NUM; ++row) {
        for (size_t column = 0; column < LINE_NUM; ++column) {
            
            if (positionStatusTable[row][column] == PORT_LOCATION_OCCUPIED && \
                chessmanStatusTable[row * LINE_NUM + column].player == player) {    
                // check '-'
                if ((column < 11 && \
                    (chessmanStatusTable[row * LINE_NUM + column + 1].player == player) && \
                    (chessmanStatusTable[row * LINE_NUM + column + 2].player == player) && \
                    (chessmanStatusTable[row * LINE_NUM + column + 3].player == player) && \
                    (chessmanStatusTable[row * LINE_NUM + column + 4].player == player)) || \
                    // check '|'
                    (row < 11 && \
                    (chessmanStatusTable[(row + 1) * LINE_NUM + column].player == player) && \
                    (chessmanStatusTable[(row + 2) * LINE_NUM + column].player == player) && \
                    (chessmanStatusTable[(row + 3) * LINE_NUM + column].player == player) && \
                    (chessmanStatusTable[(row + 4) * LINE_NUM + column].player == player)) || \
                    // check '\'
                    ((row < 11 && column < 11) && \
                    (chessmanStatusTable[(row + 1) * LINE_NUM + column + 1].player == player) && \
                    (chessmanStatusTable[(row + 2) * LINE_NUM + column + 2].player == player) && \
                    (chessmanStatusTable[(row + 3) * LINE_NUM + column + 3].player == player) && \
                    (chessmanStatusTable[(row + 4) * LINE_NUM + column + 4].player == player)) || \
                    // check '/'
                    ((row < 11 && column > 3) && \
                    (chessmanStatusTable[(row + 1) * LINE_NUM + column - 1].player == player) && \
                    (chessmanStatusTable[(row + 2) * LINE_NUM + column - 2].player == player) && \
                    (chessmanStatusTable[(row + 3) * LINE_NUM + column - 3].player == player) && \
                    (chessmanStatusTable[(row + 4) * LINE_NUM + column - 4].player == player))) {
                        return true;
                }
            }
        }
    }
    
    return false;
}
