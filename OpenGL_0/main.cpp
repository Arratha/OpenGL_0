#include <GLFW/glfw3.h>
#include <windows.h>

float vertex[] = { -1,-1,0, 1,-1,0, 1,1,0 , -1,1,0 };
float normal[] = { -1,-1,3, 1,-1,3, 1,1,3 , -1,1,3 };

void DrawRectangle()
{
    glNormal3f(0, 0, 1);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, vertex);
        glNormalPointer(GL_FLOAT, 0, normal);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void DrawVisibleCube()
{
    glPushMatrix();

    glColor3f(1, 0, 0);
    DrawRectangle();
    
    glRotatef(-90, 1, 0, 0);
    glTranslatef(0, 1, -1);

    glColor3f(0, 1, 0);
    DrawRectangle();

    glRotatef(-90, 0, 1, 0);
    glTranslatef(1, 0, 1);

    glColor3f(0, 0, 1);
    DrawRectangle();

    glPopMatrix();
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "OpenGLTest", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.1, 0.1, -0.1, 0.1, 0.2, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_NORMALIZE);

    float lightAngle = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
        glTranslatef(0, 0, -3);

        glScalef(0.5f, 0.5f, 0.5f);

        glRotatef(-60, 1, 0, 0);
        glRotatef(60, 0, 0, 1);
        glTranslatef(0.3f, 0.3f, 0);

        DrawVisibleCube();

        glPushMatrix();
            glTranslatef(0, 0, -1);

            glRotatef(lightAngle, 0, 1, 0);
            lightAngle += 1;

            float lightPosition[] = { 0,0,2,0 };
            glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

            glTranslatef(0, 0, 2);
            glScalef(0.2f, 0.2f, 0.2f);
            glColor3f(1, 1, 1);
            DrawRectangle();
        glPopMatrix();

        glPopMatrix();

        glfwSwapBuffers(window);

        glfwPollEvents();

        Sleep(1);
    }

    glfwTerminate();
    return 0;
}