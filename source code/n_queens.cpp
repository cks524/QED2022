//this solves the n-queens problem with a backtracking algorithm
#include <bits/stdc++.h>
using namespace std;

int n, grid[27][27], counter;

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

void printGrid()
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            cout << grid[i][j] << " ";
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
        //printGrid();
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
            //place queen
            grid[pos][i]=-1;
            //next column
            placeQueens(pos+1);
            //remove queen
            grid[pos][i]=0;
        }
    }
}

int main()
{
   cin >> n;
   placeQueens(0);
   cout << counter << "\n";
}
