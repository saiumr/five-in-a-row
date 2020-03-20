#include "init.h"
#define LINES_DISTANCE 38
#define CHESSMAN_RADIUS 15
#define LINE_NUM 15

/**
 * \brief All possible location of chessman.
 */
SDL_Point portPosition[LINE_NUM][LINE_NUM];

/**
 * \brief The range of every portPosition.
 */
SDL_Rect portPositionCheckRect[LINE_NUM][LINE_NUM];

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
 * \return true if point in range or not.
 */
bool portCheckIn(int x, int y);

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
 */
void chessView(int x, int y);

/**
 * 
 * \brief Change render drawColor.
 * \param render The renderer.
 * \param n The diffrent color. 0 balck  1 white 2 green  3 theme0 color  4 theme1 color
 * \param alpha Alpha should be between 0-255.
 */
void portColor(SDL_Renderer* render, int n, int alpha);

/**
 * \brief Get point or rect table subscript.
 * \param x The mouse x coordinate.
 * \param y The mouse y coordinate.
 * \return SDL_Point A point.
 */
SDL_Point getSubcript(int x, int y);