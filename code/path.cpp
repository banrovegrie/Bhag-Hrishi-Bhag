#include "main.h"

void findDist
(
    vector<vector<cell> > maze, 
    pair<int, int> next[ROWS][COLS][ROWS][COLS]
)
{
    int rows = ROWS, cols = COLS;
    int dist[rows][cols][rows][cols];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            for (int x = 0; x < rows; x++)
                for (int y = 0; y < cols; y++)
                    dist[i][j][x][y] = INF,
                    next[i][j][x][y] = {INF, INF};
    
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            dist[i][j][i][j] = 0;
            next[i][j][i][j] = {i, j};
            if(!maze[i][j].top)
                dist[i][j][i - 1][j] = 1,
                next[i][j][i - 1][j] = {i - 1, j};
            if (!maze[i][j].bottom)
                dist[i][j][i + 1][j] = 1,
                next[i][j][i + 1][j] = {i + 1, j};
            if(!maze[i][j].left)
                dist[i][j][i][j - 1] = 1,
                next[i][j][i][j - 1] = {i, j - 1};
            if(!maze[i][j].right)
                dist[i][j][i][j + 1] = 1,
                next[i][j][i][j + 1] = {i, j + 1};
        }
    }

    for (int a = 0; a < rows; a++)
        for (int b = 0; b < cols; b++)
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    for (int x = 0; x < rows; x++)
                        for (int y = 0; y < cols; y++)
                            if (dist[i][j][x][y] > dist[i][j][a][b] + dist[a][b][x][y])
                                dist[i][j][x][y] = dist[i][j][a][b] + dist[a][b][x][y],
                                next[i][j][x][y] = next[i][j][a][b];
}