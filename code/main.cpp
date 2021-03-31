#include "main.h"

void drawlines(GLfloat a, GLfloat b, GLfloat x, GLfloat y)
{
    glBegin(GL_LINES);
    {
        glVertex2f(a, b);
        glVertex2f(x, y);
    }
    glEnd();
}

/* Draw Stuff */
void draw(vector<vector<cell> > maze, GLfloat size = (float)SIZE)
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
        }       
    }
}

int main()
{
    /* OpenGL Initialisation */
    glfwInit();

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

    // Making the maze
    int rows = ROWS, cols = COLS;
    vector<vector<cell> > maze = getMaze();

    /* Render here */
    while(!glfwWindowShouldClose(window))
    {
        // background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
        draw(maze);

        // glPushMatrix();
        // { 
        // }
        // glPopMatrix();

        // call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    /* GLFW Termination */
    glfwTerminate();
    return 0;
}
