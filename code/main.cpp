#include "main.h"

/* Record the last Input */
int INPUT = 0;
int MOVE = 0;

/* Draw Lines */
void drawlines(GLfloat a, GLfloat b, GLfloat x, GLfloat y)
{
    glBegin(GL_LINES);
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(a, b);
        glVertex2f(x, y);
    }
    glEnd();
}

/* Render Function */
void draw
(
    vector<vector<cell> > maze,
    pos &hrishi, pos &shreyas, 
    pos &task1, pos &task2,
    pos &c, pos &b,
    pair<int, int> next[ROWS][COLS][ROWS][COLS], 
    GLfloat size = (float)SIZE
)
{
    int rows = ROWS, cols = COLS;

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            if (maze[i][j].bottom) 
            {
                drawlines(
                    i * size + size, j * size,
                    i * size + size, j * size + size
                );
            }
            if (maze[i][j].top) 
            {
                drawlines(
                    i * size, j * size,
                    i * size, j * size + size
                );
            }
            if (maze[i][j].right) 
            {
                drawlines(
                    i * size, j * size + size,
                    i * size + size, j * size + size
                );
            }
            if (maze[i][j].left) 
            {
                drawlines(
                    i * size, j * size,
                    i * size + size, j * size
                );
            }
        }
    }
    
    /* Draw my Sprites*/
    drawSprites(
        hrishi, shreyas, 
        task1, task2, c, b,
        maze, INPUT, 
        MOVE, next
    );
    INPUT = 0;

    return;
}

/* Process Input */
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
            /* For Escape */
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, true);
                break;
            case GLFW_KEY_W:
                // up
                INPUT = 1;
                break;
            case GLFW_KEY_S:
                // down
                INPUT = 2;
                break;
            case GLFW_KEY_A:
                // left
                INPUT = 3;
                break;
            case GLFW_KEY_D:
                // right
                INPUT = 4;
                break;
        }       
    }
}

int main()
{
    /* Initializing major variables */
    pos hrishi, shreyas, task1, task2, coin, bomb;

    /* OpenGL Initialisation */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    /* Create GLFW Window */
    GLFWwindow* window = glfwCreateWindow(
        SCREEN_WIDTH, SCREEN_HEIGHT, "Faces", NULL, NULL
    );

    /* Input */
    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
    
    /* Make Context */
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    if (window == NULL)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    /* Make sure resizing window works */
    glViewport( 0.0f, 0.0f, screenWidth, screenHeight);
    GLfloat halfScreenWidth = screenWidth / 2;
    GLfloat halfScreenHeight = screenHeight / 2;

    /* Camera Movements */
    /* 
        Specifies the part of the window to which OpenGL will draw 
        (in pixels), convert from normalised to pixels
    */
    glMatrixMode(GL_PROJECTION);
    /* 
        Replace the current matrix with the identity matrix 
        and starts us a fresh because matrix transforms 
        such as glOrpho and glRotate cumulate
        basically puts us at (0, 0, 0)
    */
    glLoadIdentity();
    /* Essentially set the coordinate system */
    glOrtho(-(int)sX, (int)eX, -(int)sY, (int)eY, -(int)Z, (int)Z);
    /*
        Default matrix mode: modelview matrix 
        defines how your objects are transformed 
        (meaning translation, rotation and scaling) 
        in your world
    */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHTING);

    // Making the maze
    int rows = ROWS, cols = COLS;
    vector<vector<cell> > maze = getMaze();
    pair<int, int> next[ROWS][COLS][ROWS][COLS];
    findDist(maze, next);

    /* Initializing Sprites*/
    initializeSprites(hrishi, shreyas, task1, task2, coin, bomb);

    /* Render here */
    while(!glfwWindowShouldClose(window))
    {
        // background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
        draw(maze, hrishi, shreyas, task1, task2, coin, bomb, next);
        
        // call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    /* GLFW Termination */
    glfwTerminate();
    return 0;
}
