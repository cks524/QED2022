//this is the combination of the two problems
#include <bits/stdc++.h>
using namespace std;

int n, grid[27][27], counter, notiling_counter, tiling_num, tile_count, white, black;

void initGrid()
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
           grid[i][j]=0;
        }
    }
}

void placeTiles(int x, int y)
{
    //if the whole board has been filled
    if (x==n)
    {
        tiling_num++;
        return;
    }
    //if the square is covered
    if (grid[x][y])
    {
        //go to next square
        if (y==n-1)
        {
            placeTiles(x+1, 0);
        }
        else
        {
            placeTiles(x, y+1);
        }
        return;
    }
    tile_count++;
    //set the square to be covered, number the tile
    grid[x][y]=tile_count;
    //try to place a left-right tile
    if (y+1<n && !grid[x][y+1])
    {
        //place it
        grid[x][y+1]=tile_count;
        //next square
        placeTiles(x, y+1);
        //remove it
        grid[x][y+1]=0;
    }
    //try to place and up-down tile
    if (x+1<n && !grid[x+1][y])
    {
        //place it
        grid[x+1][y]=tile_count;
        //next square
        if (y==n-1)
        {
            placeTiles(x+1, 0);
        }
        else
        {
            placeTiles(x, y+1);
        }
        //remove it
        grid[x+1][y]=0;
    }
    //mark the tile as uncovered
    grid[x][y]=0;
}

void printGrid()
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            if (grid[i][j]==-1)
            {
                cout << "Q ";
            }
            else
            {
                cout << "0 ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

void placeQueens(int pos)
{
    //all queens have been placed
    if (pos==n)
    {
        counter++;
        tile_count=0;
        //compare # black squares and # white squares
        if ((n*n)/2-black==(n*n+1)/2-white)
        {
            placeTiles(0, 0);
        }
        else
        {
            tiling_num=0;
            //cannot be tiled so add one to counter of arrangements not able to be tiled
            notiling_counter++;
            //printGrid();
        }
        //reset number of tiling in the case to 0
        tiling_num=0;
        return;
    }
    bool works;
    //try to place a queen
    for (int i=0; i<n; i++)
    {
        works=1;
        //check if the new queen is being attacked
        for (int j=0; j<pos; j++)
        {
            if (grid[j][i]==-1)
            {
                works=0;
                break;
            }
            if (i-(pos-j)>=0 && grid[j][i+j-pos]==-1)
            {
                works=0;
                break;
            }
            if (i+(pos-j)<n && grid[j][i+pos-j]==-1)
            {
                works=0;
                break;
            }
        }
        //if not atacked
        if (works)
        {
            //place queen and mark as covered
            grid[pos][i]=-1;
            //add to amount of white or black
            if ((pos+i)%2==0)
            {
                white++;
            }
            else
            {
                black++;
            }
            //next column
            placeQueens(pos+1);
            //remove from amount of white or black
            if ((pos+i)%2==0)
            {
                white--;
            }
            else
            {
                black--;
            }
            //remove queen and mark as not covered
            grid[pos][i]=0;
        }
    }
}

int main()
{
    cin >> n;
    placeQueens(0);
    cout << n << ": " << counter << ", " << counter-notiling_counter << "\n";
}
