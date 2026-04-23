#include<iostream>
#include"point.h"
#include"bird.h"
#include"function.h"
using namespace std;

int main()
{
    // Load the map
    char map[10][10];

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cin >> map[i][j];
        }
    }

    Chicken chicken;
    Duck duck;
    Goose goose;
    Point start;
    Point ans;

    // Chicken, Duck, and Goose search for feed in order
    for (int i = 0; i < 3; i++)
    {
        cin >> start.x >> start.y;

        switch (i)
        {
        case 0:
            ans = findFeed(&chicken, map,  start);
            break;
        case 1:
            ans = findFeed(&duck, map,  start);
            break;
        case 2:
            ans = findFeed(&goose, map,  start);
            break;
        }

        if (ans.x == -1 && ans.y == -1) cout << "can not find the feed" << endl;
        else cout << ans.x << ", " << ans.y << endl;
    }
}