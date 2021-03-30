#include "main.h"

void drawSquare(GLfloat a)
{
    GLfloat vertices[] = {
        // front face
        -a/2, +a/2, +a/2, // top left
        +a/2, +a/2, +a/2, // top right
        +a/2, -a/2, +a/2, // bottom right
        -a/2, -a/2, +a/2, // bottom left
    };

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
}

/* Draw Stuff */
void draw()
{
    int rows = ROWS, cols = COLS;
    vector<vector<cell> > maze = getMaze();
    
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            if (maze[i][j].bottom) 
            {
                // glColor4f(0, .2, 0, 0);
                glPushMatrix();
                glTranslatef(j * 2 - 2, 0, i * 2);
                glScalef(1, 1, 0.25);   // Added here
                drawSquare(2);
                glPopMatrix();
            }
            if (maze[i][j].top) 
            {
                // glColor4f(0, .2, 0, 0);
                glPushMatrix();
                glTranslatef(j * 2 + 2, 0, i * 2);
                glScalef(1, 1, 0.25);   // Added here
                drawSquare(2);
                glPopMatrix();
            }
            if (maze[i][j].right) 
            {
                // glColor4f(0, .2, 0, 0);
                glPushMatrix();
                glTranslatef(j * 2, 0, i * 2 + 2);
                glScalef(0.25, 1, 1);   // Added here
                drawSquare(2);
                glPopMatrix();
            }
            if (maze[i][j].left) 
            {
                // glColor4f(0, .2, 0, 0);
                glPushMatrix();
                glTranslatef(j * 2, 0, i * 2 - 2);
                glScalef(0.25, 1, 1);  // Added here
                drawSquare(2);
                glPopMatrix();
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
    glOrtho(-(int)X, (int)X, -(int)Y, (int)Y, -(int)Z, (int)Z);
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

    /* Render here */
    while(!glfwWindowShouldClose(window))
    {
        // background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
        draw();

        // glPushMatrix();
        // { 
        //     drawSquare(100); 
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
