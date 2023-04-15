#ifndef _PORT_H_
#define _PORT_H_

#include "init.h"
#define LINES_DISTANCE 38
#define CHESSMAN_RADIUS 15
#define LINE_NUM 15

struct chessmanStatus {
    int x;
    int y;
    int flag;
};

/**
 * \brief All possible location of chessman.
 */
extern SDL_Point portPosition[LINE_NUM][LINE_NUM];

/**
 * \brief The position whether have been occupied 0 yes 1 no.
 */
extern int positionStatusTable[LINE_NUM][LINE_NUM];

/**
 * \brief The chessman status include pos x&y, and flag indicate black with 0 or white with 1. Init null.
 */
extern struct chessmanStatus chessmanStatus[LINE_NUM * LINE_NUM];


/**
 * \brief The range of every portPosition.
 */
extern SDL_Rect portPositionCheckRect[LINE_NUM][LINE_NUM];

/**
 * 
 */
void initPositionTable();

/**
 * \brief Draw a port of five-in-a-row with diffrent theme and initialize portPosition[][].
 * 
 * \param theme The theme of port 0 or 1 currently, and 1 theme default.
 */
void initPort(int theme);

/**
 * \brief Check point is within range. 
 * 
 * \param x The x coordinate of point.
 * \param y The y coordinate of point.
 * \param flag The color of chessman view.
 * \return chessman location if point in range.
 */
SDL_Point portCheckIn(int x, int y, int flag);

/**
 * \brief Get a position of chessman.
 * \param sub_x The first subscript of portPosition Table.
 * \param sub_y The second subscript of portPosition Table.
 * \return SDL_Point coordinate of point.
 */
SDL_Point getPortPoint(int sub_x, int sub_y);

/**
 * \brief Preview where chess will location.
 * \param x The x coordinate of circle center.
 * \param y The y coordinate of circle center.
 * \param kind 1 Filled or 0 not.
 * \param flag 0 black or 1 white.
 */
void chessView(int x, int y, int kind, int flag);

/**
 * 
 * \brief Change render drawColor.
 * \param render The renderer.
 * \param n The different color. 0 black  1 white 2 green  3 theme0 color  4 theme1 color
 * \param alpha Alpha should be between 0-255.
 */
void portColor(SDL_Renderer* render, int n, int alpha);

/**
 * \brief Get point or rect table subscript.
 * \param x The mouse x coordinate.
 * \param y The mouse y coordinate.
 * \return SDL_Point A point.
 */
SDL_Point getSubscript(int x, int y);

/**
 * \brief Change status of position and chessman location table.
 * \param sub_x The x subscript of table.
 * \param sub_y The y subscript of table.
 * \param chessmanCount All chessman's number.
 * \param flag The kind of chessman 0 black 1 white.
 */
void chessmanStatusChange(int sub_x, int sub_y, int chessmanCount, int flag);

/**
 * \brief Draw chessman that have located.
 * \param chessmanCount All chessman's number.
 */
void chessmanLocationView(int chessmanCount);

#endif
