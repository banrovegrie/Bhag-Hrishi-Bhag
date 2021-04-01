#include "main.h"

class Maze
{
    public:

        struct def 
        {
            vector<vector<cell> > G;
            set<vector<int> > wallSet;
            set<vector<int> > cellSet;
        };

        def ret;

        vector<vector<cell> > G;
        set<vector<int> > wallSet;
        set<vector<int> > cellSet;
        
        def initialize
        (
            vector<vector<cell> > G, 
            int rows, int cols,
            set<vector<int> > wallSet,
            set<vector<int> > cellSet
        )
        {
            G.resize(rows, vector<cell> (cols));
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    G[i][j].top = true;
                    G[i][j].bottom = true;
                    G[i][j].left = true;
                    G[i][j].right = true;
                }
            }

            wallSet.insert({0, 0, 2});
            wallSet.insert({0, 0, 3});
            cellSet.insert({0, 0});

            def returnStruct;
            returnStruct.G = G;
            returnStruct.wallSet = wallSet;
            returnStruct.cellSet = cellSet;
            return returnStruct;
        }
        
        auto select_random(set<vector<int> > s, size_t n) 
        {
            auto it = begin(s);
            advance(it, n);
            return it;
        }

        def generateMaze
        (
            vector<vector<cell> > G, 
            int rows, int cols,
            set<vector<int> > wallSet,
            set<vector<int> > cellSet
        )
        {
            srand(time(0));
            auto r = rand() % wallSet.size(); 
            auto wall = *select_random(wallSet, r);
            
            auto x = wall[0], y = wall[1];
            
            /* 
                Regarding the values of the wall[2],
                left: 0, top: 1, right: 2, bottom: 3
            */

            if (y != 0 && wall[2] == 0 && !cellSet.count({x, y - 1}))
            {
                G[x][y].left = false;
                G[x][y - 1].right = false;
                cellSet.insert({x, y - 1});
                for (int i = 0; i < 4; i++)
                    wallSet.insert({x, y - 1, i});
            }
            else if (x != 0 && wall[2] == 1 && !cellSet.count({x - 1, y}))
            {
                G[x][y].top = false;
                G[x - 1][y].bottom = false;
                cellSet.insert({x - 1, y});
                for (int i = 0; i < 4; i++)
                    wallSet.insert({x - 1, y, i});
            }
            else if (y != cols - 1 && wall[2] == 2 && !cellSet.count({x, y + 1}))
            {
                G[x][y].right = false;
                G[x][y + 1].left = false;
                cellSet.insert({x, y + 1});
                for (int i = 0; i < 4; i++)
                    wallSet.insert({x, y + 1, i});
            }
            else if (x != rows - 1 && wall[2] == 3 && !cellSet.count({x + 1, y}))
            {
                G[x][y].bottom = false;
                G[x + 1][y].top = false;
                cellSet.insert({x + 1, y});
                for (int i = 0; i < 4; i++)
                    wallSet.insert({x + 1, y, i});
            }
            
            wallSet.erase(wall);
            
            def returnStruct;
            returnStruct.G = G;
            returnStruct.wallSet = wallSet;
            returnStruct.cellSet = cellSet;
            return returnStruct;
        }
};