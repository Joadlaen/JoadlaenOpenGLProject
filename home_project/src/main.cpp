#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

void initTriangle()
{
    //GLfloat verts[] = {
    ////-1.0f, -1.0f, // v1
    ////1.0f, -1.0f, // v2
    ////0.0f, 1.0f, // v3

    ////1.0f, -0.5f, // v2
    ////1.0f, 1.0f, // v4
    ////0.5f, 1.0f, // v3
    //    -1.0f, 1.0f,  0.0f,// v0
    //    -1.0f, -1.0f, 0.0f,// v1
    //    1.0f, -1.0f,  0.0f, // v2
    //    1.0f, 1.0f,   0.0f,// v3
    //};

    //// indices of two triangles
    //GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

        // two triangles : vertex data
    GLfloat verts[] = {
        -1.0f, 1.0f,  0.0f,// v0
        -1.0f, -1.0f, 0.0f,// v1
        1.0f, -1.0f,  0.0f, // v2
        1.0f, 1.0f,   0.0f,// v3
    };

    // indices of two triangles
    GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

    /*GLuint bufID;
    glGenBuffers(1, &bufID);
    glBindBuffer(GL_ARRAY_BUFFER, bufID);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);*/

    // create index buffer
    GLuint idxBufID;
    glGenBuffers(1, &idxBufID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBufID);

    // set buffer data for triangle index
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void drawTriangle()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


int main()
{
 GLFWwindow *window;

    // GLFW init
    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(750, 400, "Azure Renderer", NULL, NULL);
    glfwMakeContextCurrent(window);

    // loading glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Couuldn't load opengl" << std::endl;
        glfwTerminate();
        return -1;
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

    return 0;
}