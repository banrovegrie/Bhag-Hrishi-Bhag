#include "sprites.h"

void initializeSprites
(
    pos &h, pos &s, pos &t1, 
    pos &t2, pos &c, pos &b
)
{
    /* Draw my Players */
    srand(time(0));

    h.Health = 3, h.Tasks = 2,
    h.Light = 1, h.Time = 100, h.Points = 0;
    
    h.cx = (0) * SIZE + SIZE / 2;
    h.cy = (0) * SIZE + SIZE / 2;
    s.cx = ((rand() % 4) + 0) * SIZE + SIZE / 2;
    s.cy = ((rand() % 4) + 16) * SIZE + SIZE / 2;

    /* Draw my Tasks*/
    int randX = (rand() % 3) + 5;
    int randY = (rand() % 3) + 5;

    t1.cx = randX * SIZE + SIZE / 2;
    t1.cy = randY * SIZE + SIZE / 2;

    t2.cx = ((rand() % 3) + randX + 5) * SIZE + SIZE / 2;
    t2.cy = ((rand() % 3) + randY + 5) * SIZE + SIZE / 2;

    c.cx = INF, c.cy = INF, b.cx = INF, b.cy = INF;
}

void hrishiMovement
(
    pos &h, pos &s, pos &t1, pos &t2, 
    pos &c, pos &b,
    vector<vector<cell> > maze, int INPUT
)
{
    /* Movement and Collision */
    int valX = (h.cx - SIZE / 2) / SIZE;
    int valY = (h.cy - SIZE / 2) / SIZE;
        
    switch(INPUT)
    {
        case 1:
            // up
            if (!maze[valX][valY].right)
                valY++;
            break;
        case 2:
            // down
            if (!maze[valX][valY].left)
                valY--;
            break;
        case 3:
            // left
            if (!maze[valX][valY].top)
                valX--;
            break;
        case 4:
            // right
            if (!maze[valX][valY].bottom)
                valX++;
            break;
    }

    h.cx = (valX) * SIZE + SIZE / 2;
    h.cy = (valY) * SIZE + SIZE / 2;

    /* 
        Actions are described here 
    */

    // Shreyas eats Hrishi
    if (h.cx == s.cx && h.cy == s.cy)
    {
        cout << "Lmao! Hrishi just died" << endl;
        exit(0);
    }
    // Task 1
    else if (h.cx == t1.cx && h.cy == t1.cy)
    {
        t1.cx = INF, t1.cy = INF;
        s.cx = ((rand() % 4) + 0) * SIZE + SIZE / 2;
        s.cy = ((rand() % 4) + 16) * SIZE + SIZE / 2;
        h.Tasks--;
        h.Points += 30;
    }
    // Task 2
    else if (h.cx == t2.cx && h.cy == t2.cy)
    {
        t2.cx = INF, t2.cy = INF;
        c.cx = ((rand() % 4) + 16) * SIZE + SIZE / 2, 
        c.cy = ((rand() % 4) + 16) * SIZE + SIZE / 2;
        b.cx = ((rand() % 8) + 10) * SIZE + SIZE / 2, 
        b.cy = ((rand() % 8) + 10) * SIZE + SIZE / 2;
        h.Tasks--;
        h.Points += 50;
    }
    // Coin
    else if (h.cx == c.cx && h.cy == c.cy)
    {
        c.cx = INF, c.cy = INF;
        h.Points += 10;
    }
    // Bomb
    else if (h.cx == b.cx && h.cy == b.cy)
    {
        b.cx = INF, b.cy = INF;
        h.Health--;
        h.Points -= 5;
    }
    // End of Game
    else if (valX == ROWS - 1 && valY == ROWS - 1)
    {
        cout << "Congrats! Game Finished" << endl;
        exit(0);
    }
}

void shreyasMovement
(
    pos &h, pos &s, pos &t1, pos &t2, 
    pos &c, pos &b,
    vector<vector<cell> > maze, int INPUT,
    int &MOVE, pair<int, int> next[ROWS][COLS][ROWS][COLS]
)
{
    int valI = (s.cx - SIZE / 2) / SIZE;
    int valJ = (s.cy - SIZE / 2) / SIZE;
    int valX = (h.cx - SIZE / 2) / SIZE;
    int valY = (h.cy - SIZE / 2) / SIZE;

    if (MOVE % 30 == 0)
    {
        MOVE = 0;
        valI = next[valI][valJ][valX][valY].first;
        valJ = next[valI][valJ][valX][valY].second;
    }

    s.cx = (valI) * SIZE + SIZE / 2;
    s.cy = (valJ) * SIZE + SIZE / 2;
    MOVE++;
}

void drawSprites
(
    pos &h, pos &s, pos &t1, pos &t2, 
    pos &c, pos &b,
    vector<vector<cell> > maze, int INPUT,
    int &MOVE, pair<int, int> next[ROWS][COLS][ROWS][COLS]
)
{
    /* Movement */
    hrishiMovement(h, s, t1, t2, c, b, maze, INPUT);
    shreyasMovement(h, s, t1, t2, c, b, maze, INPUT, MOVE, next);

    /* Main Render */
    Sprite hrishi = Sprite();
    Sprite shreyas = Sprite();
    hrishi.renderPlayer(false, h.cx, h.cy);
    shreyas.renderPlayer(true, s.cx, s.cy);

    Sprite tasks[2];
    tasks[0].renderTasks(t1.cx, t1.cy);
    tasks[0].renderTasks(t2.cx, t2.cy);

    Sprite coin, bomb;
    coin.renderCoin(c.cx, c.cy);
    bomb.renderBomb(b.cx, b.cy);
}