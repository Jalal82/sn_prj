#include "planer.h"

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

std::vector<Point> pos_track;

planer::planer(int h, int w)
{
    height = h;
    width = w;
    map = std::vector<std::vector<int>>(height, std::vector<int>(width));

    // Will make cout much faster
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

void planer::setalphaPosition(int x, int y)
{
    alpha.x = x;
    alpha.y = y;
}

void planer::clear_pos_track()
{
    pos_track.clear();
   
   for (auto a:vect_a){
    vect_a.pop_back();
   }
}

void planer::updatealphaPosition()
{
    alpha.x = beta.x;
    alpha.y = beta.y;
}

void planer::setbetaPosition(int x, int y)
{
    beta.x = x;
    beta.y = y;
}

void planer::setthetaCells(std::vector<Point> thetaCells)
{
    for (std::vector<Point>::size_type i = 0; i < thetaCells.size(); i++)
    {
        map[thetaCells[i].x][thetaCells[i].y] = 1;
    }
}

void planer::setblkCells(int *tailX, int *tailY, int nTail)
{
    // Update the map to reflect the current state of the body
    for (int i = 0; i < nTail; i++)
    {

        map[tailX[i]][tailY[i]] = 1;
    }
}

std::vector<std::string> planer::getZetaVector()
{
    map[alpha.x][alpha.y] = 0;

    std::queue<Point> q;
    q.push(alpha);

    std::vector<std::vector<int>> dist(map.size(),
                                       std::vector<int>(map[0].size(), -1));
    dist[alpha.x][alpha.y] = 0;

    std::vector<std::vector<Point>> prev(map.size(),
                                         std::vector<Point>(map[0].size()));

    while (!q.empty())
    {
        Point curr = q.front();
        q.pop();

        if (curr.x == beta.x && curr.y == beta.y)
        {
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];

            if (inBounds(newX, newY, map.size(), map[0].size()) && map[newX][newY] == 0 && dist[newX][newY] == -1)
            {
                q.push({newX, newY});
                dist[newX][newY] = dist[curr.x][curr.y] + 1;
                prev[newX][newY] = curr;
            }
        }
    }

    std::vector<std::string> route;
    Point curr = beta;
    while (curr.x != alpha.x || curr.y != alpha.y)
    {

        vect_a.insert(vect_a.begin(),vect_b);
        // Store position
        pos_track.insert(pos_track.begin(), curr);

        Point prevPoint;
        if (curr.x < width && curr.y < height)
            prevPoint = prev[curr.x][curr.y];
        else
        {
            prevPoint = prev[width - 1][height - 1];
        }

        for (int i = 0; i < 4; i++)
        {
            if (prevPoint.x + dx[i] == curr.x && prevPoint.y + dy[i] == curr.y)
            {
                if (route.size() == 0)
                {
                    route.push_back(getDirection(i));
                    break;
                }
                else if (i == 0 && route.back() != "down" || i == 1 && route.back() != "up" || i == 2 && route.back() != "right" || i == 3 && route.back() != "left")
                {
                    route.push_back(getDirection(i));
                    break;
                }
            }
        }
        curr = prevPoint;
        int prevX = vect_b[0].x;
        int prevY = vect_b[0].y;
        int prev2X, prev2Y;
        vect_b[0].x = curr.x;
        vect_b[0].y = curr.y;
        for (int i = 1; i < nTail; i++)
        {
            prev2X = vect_b[i].x;
            prev2Y = vect_b[i].y;
            vect_b[i].x = prevX;
            vect_b[i].y = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        if (route.back() == "left")
            x--;
        if (route.back() == "right")
            x++;
        if (route.back() == "up")
            y--;

        if (route.back() == "down")
            y++;

        
    }

    reverse(route.begin(), route.end());
    ++nTail;
    return route;
}

bool planer::inBounds(int x, int y, int h, int w)
{
    return x >= 0 && x < h && y >= 0 && y < w;
}

std::string planer::getDirection(int index)
{
    if (index == 0)
        return "up";
    if (index == 1)
        return "down";
    if (index == 2)
        return "left";
    if (index == 3)
        return "right";
    return "";
}

std::vector<Point> planer::getPosTrack()
{
    return pos_track;
}

std::vector<std::vector<Point>> planer::gettailTrack()
{
    return vect_a;
}

void planer::printMap(Point curr, std::vector<Point> tails)
{
    system("cls");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == curr.x && i == curr.y)
            {
                std::cout << "S ";
            }
            else if (j == beta.x && i == beta.y)
            {
                std::cout << "F ";
            }
            else if (map[j][i] == 1)
            {
                std::cout << "X ";
            }
            else
            {
                std::cout << "  ";
            }
            for (auto cell : tails)
            {
                if (cell.x == j && cell.y == i)
                {
                    std::cout << "o";
                }
            }
        }
        std::cout << std::endl;
    }
}