// Headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>

// Namespce
using namespace std;

// Hyper parameters
#define SCREEN_HEIGHT 1000
#define SCREEN_WIDTH  1000
#define ROWS 20
#define COLS 20
#define sX 10
#define eX 190
#define sY 10
#define eY 200
#define Z 100
#define SIZE 9
#define INF 200000

struct cell
{
    bool top, bottom, left, right;
};
vector<vector<cell> > getMaze();

void findDist(
    vector<vector<cell> > maze, 
    pair<int, int> next[ROWS][COLS][ROWS][COLS]
);

struct pos 
{ 
    int Health, Tasks, Light, Time, Points;
    float cx, cy; 
};
void initializeSprites(pos &h, pos &s, pos &t1, pos &t2, pos &c, pos &b);
void drawSprites(
    pos &h, pos &s, pos &t1, pos &t2, pos &c, pos &b, 
    vector<vector<cell> > maze, int INPUT,
    int &MOVE, pair<int, int> next[ROWS][COLS][ROWS][COLS]
);