#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

void initTriangle()
{
    GLfloat verts[] = {
    -1.0f, -1.0f,
    1.0f, -1.0f,
    0.0f, 0.5f,
    };

    GLuint bufID;
    glGenBuffers(1, &bufID);
    glBindBuffer(GL_ARRAY_BUFFER, bufID);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void drawTriangle()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void main()
{
 GLFWwindow *window;

    // GLFW init
    if (!glfwInit())
    {

    }

    window = glfwCreateWindow(500, 350, "Azure Renderer", NULL, NULL);
    glfwMakeContextCurrent(window);

    // loading glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Couuldn't load opengl" << std::endl;
        glfwTerminate();
    }

    initTriangle();

    // setting the background colour, you can change the value
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    // setting the event loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        drawTriangle();


        glfwSwapBuffers(window);
    }

    glfwTerminate();

    // GLAD init
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Couuldn't load opengl" << std::endl;
        glfwTerminate();
    }

    // set background colour
    glClearColor(0.25f, 0.5f, 1.0f, 1.0f);

    // rendering loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}