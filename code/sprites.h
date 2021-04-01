#include "main.h"

class Sprite
{
    public:

        void renderPlayer
        (
            bool enemyFlag,
            float cx, float cy, 
            float r = SIZE / 4.5, int n = 100
        )
        {
            glBegin(GL_POLYGON);
            {
                for(int i = 0; i < n; i++)
                {
                    float theta = 2.0f * M_PI * float(i) / float(n);

                    float x = r * cosf(theta);      //calculate the x component
                    float y = r * sinf(theta);      //calculate the y component
                    
                    if (!enemyFlag)
                        glColor3f(1.0f, 0.0f, 1.0f);
                    else
                        glColor3f(1.0f, 0.0f, 0.0f);
                    glVertex2f(x + cx, y + cy);     //output vertex
                }   
            }
            glEnd();
        }

        void renderTasks
        (
            float cx, float cy, 
            float r = SIZE / 9, int n = 100
        )
        {
            glBegin(GL_POLYGON);
            {
                for(int i = 0; i < n; i++)
                {
                    float theta = 2.0f * M_PI * float(i) / float(n);

                    float x = r * cosf(theta);      //calculate the x component
                    float y = r * sinf(theta);      //calculate the y component
                    
                    glColor3f(0.0f, 1.0f, 1.0f);
                    glVertex2f(x + cx, y + cy);     //output vertex
                }   
            }
            glEnd();
        }

        void renderCoin
        (
            float cx, float cy, 
            float r = SIZE / 9, int n = 100
        )
        {
            glBegin(GL_POLYGON);
            {
                for(int i = 0; i < n; i++)
                {
                    float theta = 2.0f * M_PI * float(i) / float(n);

                    float x = r * cosf(theta);      //calculate the x component
                    float y = r * sinf(theta);      //calculate the y component
                    
                    glColor3f(1.0f, 1.0f, 0.0f);
                    glVertex2f(x + cx, y + cy);     //output vertex
                }   
            }
            glEnd();
        }

        void renderBomb
        (
            float cx, float cy, 
            float r = SIZE / 9, int n = 100
        )
        {
            glBegin(GL_POLYGON);
            {
                for(int i = 0; i < n; i++)
                {
                    float theta = 2.0f * M_PI * float(i) / float(n);

                    float x = r * cosf(theta);      //calculate the x component
                    float y = r * sinf(theta);      //calculate the y component
                    
                    glColor3f(0.5f, 0.5f, 0.5f);
                    glVertex2f(x + cx, y + cy);     //output vertex
                }   
            }
            glEnd();
        }
};