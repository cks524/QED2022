//solves the domino tiling problem for an n by n chessboard using a backtracking algorithm
#include <bits/stdc++.h>
using namespace std;

int n, grid[27][27];
bool visited[27][27];

unsigned long long counter;

void placeTiles(int x, int y)
{
    //if the whole board has been filled
    if (x == n)
    {
        counter++;
        return;
    }
    //if the square is covered
    if (visited[x][y])
    {
        //go to next square
        if (y == n - 1)
        {
            placeTiles(x + 1, 0);
        }
        else
        {
            placeTiles(x, y + 1);
        }
        return;
    }
    //set the square to be covered
    visited[x][y] = 1;
    //try to place a left-right tile
    if (y + 1 < n && !visited[x][y + 1])
    {
        //place it
        visited[x][y + 1] = 1;
        //next square
        placeTiles(x, y + 1);
        //remove it
        visited[x][y + 1] = 0;
    }
    //try to place and up-down tile
    if (x + 1 < n && !visited[x + 1][y])
    {
        //place it
        visited[x + 1][y] = 1;
        //next square
        if (y == n - 1)
        {
            placeTiles(x + 1, 0);
        }
        else
        {
            placeTiles(x, y + 1);
        }
        //remove it
        visited[x + 1][y] = 0;
    }
    //mark the tile as uncovered
    visited[x][y] = 0;
}

int main()
{
    cin >> n;
    placeTiles(0, 0);
    cout << counter << "\n";
}
