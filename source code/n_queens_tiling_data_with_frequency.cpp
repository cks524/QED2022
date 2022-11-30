//this is the combination of the two problems, with the data being output in a csv file
//it outputs the number of solutions and the number of those which are tileable
//in addition, for every possible number of white and black queens,
//the data shows the white/black squares distribution and the number of solutions to n-queens that satisfy this property
//lastly, it outputs the number of tilings for each solution, and the frequency of number of tilings
//it's not feasible to do this for n>=12 because one n-queens solution by itself already has a very large number of tilings
#include <bits/stdc++.h>
using namespace std;

int n, grid[27][27], counter, notiling_counter, tiling_num, tile_count, white, black;
map<int, unsigned long long> bw;
map<int, unsigned long long> tilefreq;

void initGrid()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void placeTiles(int x, int y)
{
    //if the whole board has been filled
    if (x == n)
    {
        tiling_num++;
        return;
    }
    //if the square is covered
    if (grid[x][y])
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
    tile_count++;
    //set the square to be covered, number the tile
    grid[x][y] = tile_count;
    //try to place a left-right tile
    if (y + 1 < n && !grid[x][y + 1])
    {
        //place it
        grid[x][y + 1] = tile_count;
        //next square
        placeTiles(x, y + 1);
        //remove it
        grid[x][y + 1] = 0;
    }
    //try to place and up-down tile
    if (x + 1 < n && !grid[x + 1][y])
    {
        //place it
        grid[x + 1][y] = tile_count;
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
        grid[x + 1][y] = 0;
    }
    //mark the tile as uncovered
    grid[x][y] = 0;
}

void printGrid()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == -1)
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
    if (pos == n)
    {
        counter++;
        tile_count = 0;
        //compare # black squares and # white squares
        if ((n * n) / 2 - black == (n * n + 1) / 2 - white)
        {
            placeTiles(0, 0);
        }
        else
        {
            tiling_num = 0;
            //cannot be tiled so add one to counter of arrangements not able to be tiled
            notiling_counter++;
            //printGrid();
        }
        //add to amount of white queens and frequency of amount of tilings
        bw[white]++;
        tilefreq[tiling_num]++;
        //reset number of tiling in the case to 0
        tiling_num = 0;
        return;
    }
    bool works;
    //try to place a queen
    for (int i = 0; i < n; i++)
    {
        works = 1;
        //check if the new queen is being attacked
        for (int j = 0; j < pos; j++)
        {
            if (grid[j][i] == -1)
            {
                works = 0;
                break;
            }
            if (i - (pos - j) >= 0 && grid[j][i + j - pos] == -1)
            {
                works = 0;
                break;
            }
            if (i + (pos - j) < n && grid[j][i + pos - j] == -1)
            {
                works = 0;
                break;
            }
        }
        //if not attacked
        if (works)
        {
            //place queen and mark as covered
            grid[pos][i] = -1;
            //add to amount of white or black
            if ((pos + i) % 2 == 0)
            {
                white++;
            }
            else
            {
                black++;
            }
            //next column
            placeQueens(pos + 1);
            //remove from amount of white or black
            if ((pos + i) % 2 == 0)
            {
                white--;
            }
            else
            {
                black--;
            }
            //remove queen and mark as not covered
            grid[pos][i] = 0;
        }
    }
}

int main()
{
    cin >> n;
    counter = 0;
    placeQueens(0);
    //puts the data into a csv file, which can be opened with excel
    ofstream outfile;
    //the name of the csv is going to be nqueens.csv, where n is the number
    string filename = to_string(n) + "queens.csv";
    outfile.open(filename);
    outfile << "\n";
    outfile << "N, #Solutions, Can be Tiled\n";
    outfile << n << "," << counter << "," << counter - notiling_counter << "\n\n";
    outfile << "White Queens, Black Queens, White Squares, Black Squares, Arrangements\n";
    for (auto x : bw)
    {
        outfile << x.first << ", " << n - x.first << ", " << (n * n + 1) / 2 - x.first << ", " << (n * n) / 2 - n + x.first << ", " << x.second << "\n";
    }
    outfile << "\nTilings, Frequency\n";
    for (auto x : tilefreq)
    {
        outfile << x.first << ", " << x.second << " \n";
    }
}
