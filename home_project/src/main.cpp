#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


#include "shader.h"

static Shader shader;

float rot_x = 0;
float rot_y = 0;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_LEFT) 
    {
        rot_y -= 5.0;
    }
    else if (key == GLFW_KEY_RIGHT /*&& action == GLFW_PRESS*/) 
    {
        rot_y += 5.0;
    } 
    if (key == GLFW_KEY_DOWN) 
    {
        rot_x += 5.0;
    }
    else if (key == GLFW_KEY_UP) 
    {
        rot_x -= 5.0;
    }


    glm::mat4 mat_scale = glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
    glm::mat4 mat_rot_y = glm::rotate(glm::radians(rot_y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 mat_rot_x = glm::rotate(glm::radians(rot_x), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 mat_modelview = mat_rot_x * mat_rot_y * mat_scale;

    GLuint modelview_loc = glGetUniformLocation(shader.program, "modelview");
    glUniformMatrix4fv(modelview_loc, 1, GL_FALSE, &mat_modelview[0][0]);
}

void initShader(std::string pathVert, std::string pathFrag)
{
    shader.read_source(pathVert.c_str(), pathFrag.c_str());

    shader.compile();
    glUseProgram(shader.program);
}

void initTriangle()
{
    
    
    // cube vertex data with RGB colour components
    GLfloat verts[] = {
        -1.0f, 1.0f,  1.0f, // v0
        0.0f, 1.0f,  0.0f,  // v0 colour green
        -1.0f, -1.0f, 1.0f, // v1
        0.0f, 0.0f, 0.0f,   // v1 colour black
        1.0f, -1.0f,  1.0f, // v2
        1.0f, 0.0f,  0.0f,  // v2 colour red
        1.0f, 1.0f,   1.0f, // v3
        1.0f, 1.0f,   0.0f, // v3 colour yellow

        -1.0f, 1.0f, -1.0f, // v4
        0.0f, 1.0f,  1.0f,  // v4 colour cyan
        -1.0f, -1.0f, -1.0f, // v5
        0.0f, 0.0f, 1.0f,   // v5 colour blue
        1.0f, -1.0f,  -1.0f, // v6
        1.0f, 0.0f,  1.0f,  // v6 colour magenta
        1.0f, 1.0f,  -1.0f, // v7
        1.0f, 1.0f,  1.0f, // v7 colour white
    };

    // indices of 12 triangles of a cube
    GLuint indices[] = {
        0, 1, 2,  0, 2, 3,
        1, 5, 2,  5, 6, 2,
        0, 3, 4,  4, 3, 7,
        3, 2, 7,  2, 6, 7,
        1, 0, 4,  1, 4, 5,
        7, 6, 4,  4, 6, 5
    };


    GLuint vertbufID;
    glGenBuffers(1, &vertbufID);
    glBindBuffer(GL_ARRAY_BUFFER, vertbufID);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    
    // set colour attributes
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));

    // create index buffer
    GLuint idxBufID;
    glGenBuffers(1, &idxBufID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBufID);

    // set buffer data for triangle index
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glm::mat4 mat_scale = glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
    glm::mat4 mat_projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

    glm::mat4 mat_modelview = mat_scale;

    GLuint modelview_loc = glGetUniformLocation(shader.program, "modelview");
    glUniformMatrix4fv(modelview_loc, 1, GL_FALSE, &mat_modelview[0][0]);

    // you must set the orthographic projection to get correct rendering with depth
    GLuint projection_loc = glGetUniformLocation(shader.program, "projection");
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, &mat_projection[0][0]);


}

void drawTriangle()
{

    glColor3f(1.0f, 1.0f, 0.0f);
    // draw triangle using indices
    glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0);


    //wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


int main()
{
 GLFWwindow *window;

    // GLFW init
    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(640, 640, "Azure Renderer", NULL, NULL);
    glfwMakeContextCurrent(window);

    // register the key event callback function
    glfwSetKeyCallback(window, key_callback);

    // loading glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Couuldn't load opengl" << std::endl;
        glfwTerminate();
        return -1;
    }

    // for both VSCode and Visual Studio
    initShader("shaders/colour.vert", "shaders/colour.frag");


    initTriangle();


    glEnable(GL_DEPTH);

    // setting the background colour, you can change the value
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    // setting the event loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawTriangle();


        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
