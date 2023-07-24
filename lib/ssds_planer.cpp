// #include "ssds_planer.h"
// int dx[] = {0, 0, -1, 1};
// int dy[] = {-1, 1, 0, 0};
// std::vector<Point> pos_track;
// /// @brief
// /// @param h
// /// @param w
// ssds_planer::ssds_planer(int h, int w)
// {
//     height = h;
//     width = w;
//     map = std::vector<std::vector<int>>(height, std::vector<int>(width));
// }
// void ssds_planer::setalphaPosition(int x, int y)
// {
//     alpha.x = x;
//     alpha.y = y;
// }

// void ssds_planer::setbetaPosition(int x, int y)
// {
//     beta.x = x;
//     beta.y = y;
// }

// void ssds_planer::setthetaCells(std::vector<Point> thetaCells)
// {
//     for (std::vector<Point>::size_type i = 0; i < thetaCells.size(); i++)
//     {
//         map[thetaCells[i].x][thetaCells[i].y] = 1;
//     }
// }

// std::vector<std::string> ssds_planer::getZetaVector(int nTail, int *tailX, int *tailY)
// {

//     // Update the map to reflect the current state of the snake

//     for (int i = 0; i < nTail; i++)
//     {

//         map[tailX[i]][tailY[i]] = 1;
//     }

//     map[alpha.x][alpha.y] = 0;

//     std::queue<Point> q;
//     q.push(alpha);

//     std::vector<std::vector<int>> dist(map.size(),
//                                        std::vector<int>(map[0].size(), -1));
//     dist[alpha.x][alpha.y] = 0;

//     std::vector<std::vector<Point>> prev(map.size(),
//                                          std::vector<Point>(map[0].size()));

//     while (!q.empty())
//     {
//         Point curr = q.front();
//         q.pop();

//         if (curr.x == beta.x && curr.y == beta.y)
//         {
//             break;
//         }

//         for (int i = 0; i < 4; i++)
//         {
//             if (curr.x + dx[i] <= width && curr.x + dx[i] >= 0 && curr.y + dy[i] <= height && curr.y + dy[i] >= 0)
//             {
//                 int newX = curr.x + dx[i];
//                 int newY = curr.y + dy[i];

//                 if (inBounds(newX, newY, map.size(), map[0].size()) && map[newX][newY] == 0 && dist[newX][newY] == -1)
//                 {
//                     q.push(
//                         {newX, newY});
//                     dist[newX][newY] = dist[curr.x][curr.y] + 1;
//                     prev[newX][newY] = curr;
//                 }
//             }
//         }
//     }

//     route.clear();
//     curr = beta;
//     while (curr.x != alpha.x || curr.y != alpha.y)
//     {
//         // print the map with the current position of the alpha
//         // printMap(curr);
//         // Store position
//         // pos_track.insert(pos_track.begin(), curr);
//         prevPoint;
//         if (curr.x < width && curr.y < height)
//             prevPoint = prev[curr.x][curr.y];
//         else
//         {
//             prevPoint = prev[width - 1][height - 1];
//         }

//         for (int i = 0; i < 4; i++)
//         {
//             if (prevPoint.x + dx[i] == curr.x && prevPoint.y + dy[i] == curr.y)
//             {
//                 // std::cout << route.size() << std::endl;
//                 if (route.size() == 0)
//                 {
//                     route.push_back(getDirection(i));
//                     break;
//                 }
//                 else if (i == 0 && route.back() != "down" || i == 1 && route.back() != "up" || i == 2 && route.back() != "right" || i == 3 && route.back() != "left")
//                 {
//                     route.push_back(getDirection(i));
//                     break;
//                 }
//             }
//         }
//         curr = prevPoint;
//     }

//     reverse(route.begin(), route.end());
//     return route;
// }

// bool ssds_planer::inBounds(int x, int y, int h, int w)
// {
//     return x >= 0 && x < h && y >= 0 && y < w;
// }

// std::string ssds_planer::getDirection(int index)
// {
//     if (index == 0)
//         return "up";
//     if (index == 1)
//         return "down";
//     if (index == 2)
//         return "left";
//     if (index == 3)
//         return "right";
//     return "";
// }

// std::vector<Point> ssds_planer::getPosTrack()
// {
//     return pos_track;
// }

// // std::vector<Point> ssds_planer::clearPosTrack()
// // {
// //     return pos_track;
// // }

// void ssds_planer::printMap(Point curr)
// {
//     for (int i = 0; i < height; i++)
//     {
//         for (int j = 0; j < width; j++)
//         {
//             if (j == curr.x && i == curr.y)
//             {
//                 std::cout << "S ";
//             }
//             else if (j == beta.x && i == beta.y)
//             {
//                 std::cout << "F ";
//             }
//             else if (map[j][i] == 1)
//             {
//                 std::cout << "X ";
//             }
//             else
//             {
//                 std::cout << "# ";
//             }
//         }
//         std::cout << std::endl;
//     }
//     std::cout << "\n";
// }
#include "ssds_planer.h"
#include <queue>
#include <vector>
#include <cmath>

const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};



ssds_planer::ssds_planer(int h, int w) : height(h), width(w), map(h, std::vector<int>(w, 0)) {}

void ssds_planer::setAlphaPosition(int x, int y) {
    alpha.x = x;
    alpha.y = y;
}

void ssds_planer::setBetaPosition(int x, int y) {
    beta.x = x;
    beta.y = y;
}

void ssds_planer::setThetaCells(const std::vector<Point>& thetaCells) {
    for (const auto& thetaCell : thetaCells) {
        map[thetaCell.x][thetaCell.y] = 1;
    }
}

std::vector<std::string> ssds_planer::getZetaVector(int nTail, int* tailX, int* tailY) {
    // Update the map to reflect the current state of the snake
    for (int i = 0; i < nTail; i++) {
        map[tailX[i]][tailY[i]] = 1;
    }

    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::vector<std::vector<Cell*>> cells(height, std::vector<Cell*>(width, nullptr));
    std::priority_queue<Cell> openSet;

    Cell* start = new Cell(alpha.x, alpha.y, 0, heuristic(alpha.x, alpha.y), nullptr);
    cells[alpha.x][alpha.y] = start;
    openSet.push(*start);

    while (!openSet.empty()) {
        Cell current = openSet.top();
        openSet.pop();

        if (current.x == beta.x && current.y == beta.y) {
            break;
        }

        visited[current.x][current.y] = true;

        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (inBounds(newX, newY) && !visited[newX][newY] && map[newX][newY] == 0) {
                int newG = current.g + 1;
                int newH = heuristic(newX, newY);
                int newF = newG + newH;

                Cell* neighbor = cells[newX][newY];
                if (neighbor == nullptr || newF < neighbor->f) {
                    if (neighbor != nullptr) {
                        openSet = removeCellFromPriorityQueue(openSet, *neighbor);
                    }

                    Cell* newCell = new Cell(newX, newY, newG, newH, &current);
                    cells[newX][newY] = newCell;
                    openSet.push(*newCell);
                }
            }
        }
    }

    std::vector<std::string> route;
    if (cells[beta.x][beta.y] != nullptr) {
        Cell* current = cells[beta.x][beta.y];

        while (current->parent != nullptr) {
            int dx = current->x - current->parent->x;
            int dy = current->y - current->parent->y;
            route.push_back(getDirection(dx, dy));
            current = current->parent;
        }
    }

    cleanUpMemory(cells);

    std::reverse(route.begin(), route.end());
    return route;
}

bool ssds_planer::inBounds(int x, int y) {
    return x >= 0 && x < height && y >= 0 && y < width;
}

int ssds_planer::heuristic(int x, int y) {
    return std::abs(x - beta.x) + std::abs(y - beta.y);
}

std::string ssds_planer::getDirection(int dx, int dy) {
    if (dx == -1 && dy == 0)
        return "up";
    if (dx == 1 && dy == 0)
        return "down";
    if (dx == 0 && dy == -1)
        return "left";
    if (dx == 0 && dy == 1)
        return "right";
    return "";
}

std::priority_queue<Cell> ssds_planer::removeCellFromPriorityQueue(std::priority_queue<Cell>& pq, const Cell& cell) {
    std::priority_queue<Cell> newPQ;
    while (!pq.empty()) {
        Cell top = pq.top();
        pq.pop();
        if (top.x == cell.x && top.y == cell.y) {
            break;
        }
        newPQ.push(top);
    }
    while (!pq.empty()) {
        Cell top = pq.top();
        pq.pop();
        newPQ.push(top);
    }
    return newPQ;
}

void ssds_planer::cleanUpMemory(std::vector<std::vector<Cell*>>& cells) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (cells[i][j] != nullptr) {
                delete cells[i][j];
                cells[i][j] = nullptr;
            }
        }
    }
}

void ssds_planer::printMap(Point curr) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == curr.x && i == curr.y) {
                std::cout << "S ";
            } else if (j == beta.x && i == beta.y) {
                std::cout << "F ";
            } else if (map[i][j] == 1) {
                std::cout << "X ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
