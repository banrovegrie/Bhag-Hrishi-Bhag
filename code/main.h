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
#define eY 190
#define Y 100
#define Z 100
#define SIZE 9

struct cell
{
    bool top, bottom, left, right;
};

vector<vector<cell> > getMaze();