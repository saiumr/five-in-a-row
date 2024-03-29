#ifndef _DRAW_CIRCLE_H_
#define _DRAW_CIRCLE_H_
/**
 * \brief Draw a circle filled or not.
 * 
 * \param renderer The renderer which should draw a circle.
 * \param x The x_coordinate of circle center.
 * \param y The y_coordinate of circle center.
 * \param radius The radius of circle.
 * \param flag The mode of circle with 1 filled or 0 not.
 */
void drawCircle(SDL_Renderer* renderer, int x, int y, int radius, int flag);
#endif