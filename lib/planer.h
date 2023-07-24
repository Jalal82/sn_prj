#ifndef PLANER_H
#define PLANER_H

#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <algorithm>

struct Point
{
    int x, y;
};
/// @brief
class planer
{
public:
    planer(int h, int w);

    void setalphaPosition(int x, int y);

    void updatealphaPosition();

    void setbetaPosition(int x, int y);

    void setthetaCells(std::vector<Point> thetaCells);

    void setblkCells(int *tailX, int *tailY, int nTail);

    std::vector<std::string> getZetaVector();

    std::vector<Point> getPosTrack();

    std::vector<std::vector<Point>> gettailTrack();

    void clear_pos_track();

    void printMap(Point curr, std::vector<Point> tails);

private:
    int height, width;
    std::vector<std::vector<int>> map;

    Point alpha, beta;

    int nTail = 0;
    int tailX[100], tailY[100];
    int x, y;

    bool inBounds(int x, int y, int h, int w);

    std::string getDirection(int index);
    std::vector<Point> pos_track;

    std::vector<std::vector<Point>> vect_a;
   
    std::vector<Point> vect_b{{0,0}};
};

#endif
// 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