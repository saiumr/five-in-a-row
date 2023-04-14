#include "port.h"
#include "DrawCircle.h"

SDL_Point portPosition[LINE_NUM][LINE_NUM];
int positionStatusTable[LINE_NUM][LINE_NUM];
struct chessmanStatus chessmanStatus[LINE_NUM * LINE_NUM];
SDL_Rect portPositionCheckRect[LINE_NUM][LINE_NUM];

void portColor(SDL_Renderer* render, int n, int alpha) {
    switch (n) {
    case 0:
        SDL_SetRenderDrawColor(render, 0, 0, 0, alpha);  //black
        break;
    case 1:
        SDL_SetRenderDrawColor(render, 255, 255, 255, alpha);  //white
        break;
    case 2:
        SDL_SetRenderDrawColor(render, 0, 255, 0, alpha);  //green
        break;
    case 3:
        SDL_SetRenderDrawColor(render, 35, 46, 60, alpha);  //theme0 color
        break;
    case 4:
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
        // 初始化落点位置表和检测范围表
        for (posCount = 0; posCount < LINE_NUM; ++posCount) {
            int x = (posCount + 1) * LINES_DISTANCE;
            int y = (drawCount + 1) * LINES_DISTANCE;

            portPosition[drawCount][posCount].x = x;
            portPosition[drawCount][posCount].y = y;

            portPositionCheckRect[drawCount][posCount].w = checkRectLength;
            portPositionCheckRect[drawCount][posCount].h = checkRectLength;
            portPositionCheckRect[drawCount][posCount].x = x - CHESSMAN_RADIUS;
            portPositionCheckRect[drawCount][posCount].y = y - CHESSMAN_RADIUS;

            positionStatusTable[drawCount][posCount] = 1;
        }
    }
}

void initPort(int theme) {
    SDL_Rect rect = {0, 0, WINDOW_HEIGHT, WINDOW_HEIGHT};
    int d_xy = LINE_NUM * LINES_DISTANCE;
    int drawCount;
    int posCount;
    
    if (theme == 0) {
        portColor(render, 3, 255);
        SDL_RenderFillRect(render, &rect);
        portColor(render, 2, 255);
        // 两边空出一样的大小
        for (drawCount = 0; drawCount < LINE_NUM; ++drawCount) {
            SDL_RenderDrawLine(render, LINES_DISTANCE, (drawCount + 1) * LINES_DISTANCE, d_xy, (drawCount + 1) * LINES_DISTANCE);
            SDL_RenderDrawLine(render, (drawCount + 1) * LINES_DISTANCE, LINES_DISTANCE, (drawCount + 1) * LINES_DISTANCE, d_xy);
        }
        portColor(render, 0, 255);
    }
    else {
        portColor(render, 4, 255);
        SDL_RenderFillRect(render, &rect);
        portColor(render, 0, 255);
        // SDL_RenderSetViewport(render, &rect);
        // 两边空出一样的大小
        for (drawCount = 0; drawCount < LINE_NUM; ++drawCount) {
            SDL_RenderDrawLine(render, LINES_DISTANCE, (drawCount + 1) * LINES_DISTANCE, d_xy, (drawCount + 1) * LINES_DISTANCE);
            SDL_RenderDrawLine(render, (drawCount + 1) * LINES_DISTANCE, LINES_DISTANCE, (drawCount + 1) * LINES_DISTANCE, d_xy);
        }
    }
}

SDL_Point getSubcript(int x, int y) {
    SDL_Point point;

    // mark : nnmmb! 纵向相除得到行数  横向相除得到列数
    point.x = y / LINES_DISTANCE - 1;
    point.y = x / LINES_DISTANCE - 1;
    if (point.x == -1) point.x = 0;
    if (point.y == -1) point.y = 0;

    return point;
}

SDL_Point getPortPoint(int sub_x, int sub_y) {
    SDL_Point point = {portPosition[sub_x][sub_y].x, portPosition[sub_x][sub_y].y};
    return point;
}

void chessView(int x, int y, int kind, int flag) {
    if (flag == 1) {
        portColor(render, 1, 255);
        drawCircle(render, x, y, CHESSMAN_RADIUS, kind);
        portColor(render, 0, 255);    
    }
    else {
        portColor(render, 0, 255);
        drawCircle(render, x, y, CHESSMAN_RADIUS, kind);
        portColor(render, 0, 255);
    }
}

SDL_Point portCheckIn(int x, int y, int flag) {
    SDL_Point chessLocation;
    // 超出棋盘的范围
    if (x > WINDOW_HEIGHT) {
        chessLocation.x = -1;
        chessLocation.y = -1;
    }
    else {
        SDL_Point point = {x, y};
        SDL_Point point_sub = getSubcript(x, y);

        int pos_x = point_sub.x;
        int pos_y = point_sub.y;
        
        int sub_rx = pos_x + 1;
        int sub_by = pos_y + 1;

        // TODO: 给矩形增加是否被检测点在其中的标志，检测到置为0，未检测到置为1
        // TODO: 在场地位置表中增加是否有棋子在的标志，后期还要添加是黑棋子还是白棋子，0有1无，0黑1白
        // 自左上角开始顺时针检查点是否在矩形内
        if(SDL_PointInRect(&point, &portPositionCheckRect[pos_x][pos_y])) {
            chessView(getPortPoint(pos_x, pos_y).x, getPortPoint(pos_x, pos_y).y, 0, flag);
            chessLocation.x = pos_x;
            chessLocation.y = pos_y;
        }
        else if(SDL_PointInRect(&point, &portPositionCheckRect[sub_rx][pos_y])) {
            chessView(getPortPoint(sub_rx, pos_y).x, getPortPoint(sub_rx, pos_y).y, 0, flag);
            chessLocation.x = sub_rx;
            chessLocation.y = pos_y;
        }
        else if(SDL_PointInRect(&point, &portPositionCheckRect[sub_rx][sub_by])) {
            chessView(getPortPoint(sub_rx, sub_by).x, getPortPoint(sub_rx, sub_by).y, 0, flag);
            chessLocation.x = sub_rx;
            chessLocation.y = sub_by;
        }
        else if(SDL_PointInRect(&point, &portPositionCheckRect[pos_x][sub_by])) {
            chessView(getPortPoint(pos_x, sub_by).x, getPortPoint(pos_x, sub_by).y, 0, flag);
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


void chessmanStatusChange(int sub_x, int sub_y, int chessmanCount, int flag) {
    // 外部chessmanCount率先增加了1
    // 把记录落点的表改成一维的了，好操作，nice啊
    int sub_locatedChessman = chessmanCount - 1;

    if (positionStatusTable[sub_x][sub_y] != 0) {
        positionStatusTable[sub_x][sub_y] = 0;
        chessmanStatus[sub_locatedChessman].x = portPosition[sub_x][sub_y].x;
        chessmanStatus[sub_locatedChessman].y = portPosition[sub_x][sub_y].y;
        chessmanStatus[sub_locatedChessman].flag = flag;
    }
}

void chessmanLocationView(int chessmanCount) {
    int sub_statusTable;
    for (sub_statusTable = 0; sub_statusTable < chessmanCount; ++sub_statusTable) {
        chessView(chessmanStatus[sub_statusTable].x, chessmanStatus[sub_statusTable].y, 1, chessmanStatus[sub_statusTable].flag);
    } 
}