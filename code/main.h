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
#define X 100
#define Y 100
#define Z 100

struct cell
{
    bool top, bottom, left, right;
};

vector<vector<cell> > getMaze();