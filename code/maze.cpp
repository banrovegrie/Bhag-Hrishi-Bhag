#include "maze.h"

vector<vector<cell> > getMaze()
{
    int rows = ROWS, cols = COLS;
    Maze maze = Maze();
    
    maze.ret = maze.initialize(
        maze.G, rows, cols, maze.wallSet, maze.cellSet
    );

    maze.G = maze.ret.G;
    maze.wallSet = maze.ret.wallSet;
    maze.cellSet = maze.ret.cellSet;

    while (maze.cellSet.size() < rows * cols)
    {
        maze.ret = maze.generateMaze(
            maze.G, rows, cols, maze.wallSet, maze.cellSet
        );

        maze.G = maze.ret.G;
        maze.wallSet = maze.ret.wallSet;
        maze.cellSet = maze.ret.cellSet;
    }

    return maze.G;
}

int test()
{
    int rows = ROWS, cols = COLS;
    Maze maze = Maze();
    
    maze.ret = maze.initialize(
        maze.G, rows, cols, maze.wallSet, maze.cellSet
    );

    maze.G = maze.ret.G;
    maze.wallSet = maze.ret.wallSet;
    maze.cellSet = maze.ret.cellSet;

    while (maze.cellSet.size() < rows * cols && !maze.wallSet.empty())
    {
        maze.ret = maze.generateMaze(
            maze.G, rows, cols, maze.wallSet, maze.cellSet
        );

        maze.G = maze.ret.G;
        maze.wallSet = maze.ret.wallSet;
        maze.cellSet = maze.ret.cellSet;
    }

    for(int i = 0; i < 2*rows; i++)
    {
        cout << "_";
    }
    cout << endl;
    
    for (int i = 0; i < rows; i++)
    {
        cout << "|";
        for (int j = 0; j < cols; j++)
        {
            cell c = maze.G[i][j];
            cout << (c.bottom == 0 ? " " : "_");

            if (c.right == 0)
                cout << " ";
            else 
                cout << "|";
        }
        cout << endl;
    }

    return 0;
}