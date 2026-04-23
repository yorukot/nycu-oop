#include<queue>
#include"point.h"
#include"bird.h"
#include"function.h"
using namespace std;

Point findFeed(Bird* b, char map[10][10], Point start)
{
    queue<Point> q;
    bool visit[10][10] = {false};
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {1, -1, 0, 0};

    // TODO

    // Use BFS to find the nearest feed

    // You must iterate through the four directions in the exact order defined by dx and dy

    // You must use canWalk() to check if the bird can move onto a tile

    // When you reach the feed tile, return its position

    // If feed is not found, return {-1, -1}
    
    //
}