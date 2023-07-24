// #ifndef SSDS_PLANER_H
// #define SSDS_PLANER_H

// #include <vector>
// #include <string>
// #include <queue>
// #include <iostream>
// #include <algorithm>

// struct Point
// {
//     int x, y;
// };
// /// @brief 
// class ssds_planer
// {
// public:
//     ssds_planer(int h, int w);

//     void setalphaPosition(int x, int y);

//     void setbetaPosition(int x, int y);

//     void setthetaCells(std::vector<Point> thetaCells);

//     std::vector<std::string> getZetaVector(int nTail,int* tailX, int* tailY);

    

//     std::vector<Point> getPosTrack();

//     void printMap(Point curr);

// private:
//     int height, width;
//     std::vector<std::vector<int>> map;

//     Point alpha, beta;

//     bool inBounds(int x, int y, int h, int w);

//     std::string getDirection(int index);

//     Point curr;
//     std::vector<std::string> route;
//     Point prevPoint;

//     std::vector<Point> pos_track;
// };

// #endif

#ifndef SSDS_PLANER_H
#define SSDS_PLANER_H

#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <algorithm>

struct Point {
    int x, y;
};

struct Cell {
    int x;
    int y;
    int g;
    int h;
    int f;
    Cell* parent;

    Cell(int x, int y, int g, int h, Cell* parent) : x(x), y(y), g(g), h(h), parent(parent) {
        f = g + h;
    }

    bool operator<(const Cell& other) const {
        return f > other.f; // Reverse order for min heap
    }
};

class ssds_planer {
public:
    ssds_planer(int h, int w);

    void setAlphaPosition(int x, int y);

    void setBetaPosition(int x, int y);

    void setThetaCells(const std::vector<Point>& thetaCells);

    std::vector<std::string> getZetaVector(int nTail, int* tailX, int* tailY);

    std::vector<Point> getPosTrack();

    void printMap(Point curr);

private:
    int height, width;
    std::vector<std::vector<int>> map;

    Point alpha, beta;

    bool inBounds(int x, int y);

    std::string getDirection(int dx, int dy);

    int heuristic(int x, int y);

    std::priority_queue<Cell> removeCellFromPriorityQueue(std::priority_queue<Cell>& pq, const Cell& cell);

    void cleanUpMemory(std::vector<std::vector<Cell*>>& cells);
};

#endif
