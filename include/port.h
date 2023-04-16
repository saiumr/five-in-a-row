#ifndef _PORT_H_
#define _PORT_H_

#include "init.h"
#define LINES_DISTANCE 38
#define CHESSMAN_RADIUS (LINES_DISTANCE/2 - 4)
#define LINE_NUM 15

typedef enum {
    PLAYER_BLACK = 0,
    PLAYER_WHITE
} Player;

typedef struct {
    int x;
    int y;
    Player player;
} Chessman_Status;

typedef enum {
    PORT_COLOR_BLACK = 0,
    PORT_COLOR_WHITE,
    PORT_COLOR_GREEN,
    PORT_COLOR_LIGHT,
    PORT_COLOR_DARK
} Port_Color;

typedef enum {
    PORT_THEME0 = 0,
    PORT_THEME1
} Port_Theme;


/**
 * \brief Record the center position of all chess pieces that should be drawn.
 */
extern SDL_Point portPositionTable[LINE_NUM][LINE_NUM];

/**
 * \brief The position whether have been occupied 0 yes 1 no.
 */
extern int positionStatusTable[LINE_NUM][LINE_NUM];

/**
 * \brief The chessman status include pos x&y, and flag indicate black with 0 or white with 1. Init null.
 */
extern Chessman_Status chessmanStatusTable[LINE_NUM * LINE_NUM];


/**
 * \brief The range of every portPositionTable.
 */
extern SDL_Rect portPositionTableCheckRect[LINE_NUM][LINE_NUM];

/**
 * \brief initialize portPositionTable, portPositionTableCheckRect and positionStatusTable
 */
void initPositionTable();

/**
 * \brief Draw a port of five-in-a-row with different theme and initialize portPositionTable[][].
 * 
 * \param theme The theme of port 0 or 1 currently, and 1 theme default.
 */
void drawPort(Port_Theme theme);

/**
 * \brief Check point is within range. 
 * 
 * \param x The x coordinate of point.
 * \param y The y coordinate of point.
 * \param flag The color of chessman view.
 * \return chessman location if point in range.
 */
SDL_Point portCheckIn(int x, int y, Player player);

/**
 * \brief Change status of position and chessman location table.
 * \param sub_x The x subscript of table.
 * \param sub_y The y subscript of table.
 * \param chessmanCount All chessman's number.
 * \param flag The kind of chessman 0 black 1 white.
 */
void chessmanStatusTableChange(int sub_x, int sub_y, int chessmanCount, Player player);

/**
 * \brief Draw chessman that have located.
 * \param chessmanCount All chessman's number.
 */
void chessmanLocationView(int chessmanCount);

#endif
