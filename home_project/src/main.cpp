#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


#include "shader.h"
#include "mesh.h"
#include "Node.h"

//static Shader shader;
//
//glm::mat4 matModelRoot = glm::mat4(1.0);
//glm::mat4 matView = glm::mat4(1.0);
//glm::mat4 matProj = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
//
//glm::mat4 matRoot = glm::mat4(1.0);
//float rot_x = 0;
//float rot_y = 0;
//
//glm::vec3 lightPos = glm::vec3(5.0f, 5.0f, 10.0f);
//glm::vec3 ViewPos = glm::vec3(0.0f, 0.0f, 5.0f);
//
//GLuint blinnShader;
//GLuint phongShader;
static Shader shader;

glm::mat4 matModelRoot = glm::mat4(1.0);
glm::mat4 matView = glm::mat4(1.0);
glm::mat4 matProj = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);

glm::vec3 lightPos = glm::vec3(5.0f, 10.0f, 20.0f);
glm::vec3 ViewPos = glm::vec3(0.0f, 0.0f, 10.0f);

GLuint blinnShader;
GLuint phongShader;



void key_callback(GLFWwindow* window, int key, int scancode, int action, int modes)
{
    glm::mat4 mat = glm::mat4(1.0);

    float angleStep = 5.0f;
    float transStep = 1.0f;

    //if (key == GLFW_KEY_LEFT) 
    //{
    //    rot_y -= 5.0;
    //}
    //else if (key == GLFW_KEY_RIGHT /*&& action == GLFW_PRESS*/) 
    //{
    //    rot_y += 5.0;
    //} 
    //if (key == GLFW_KEY_DOWN) 
    //{
    //    rot_x += 5.0;
    //}
    //else if (key == GLFW_KEY_UP) 
    //{
    //    rot_x -= 5.0;
    //}



    if (action == GLFW_PRESS)
    {

        if (GLFW_KEY_LEFT == key) {
            // pan left, rotate around Y, CCW
            mat = glm::rotate(glm::radians(-angleStep), glm::vec3(0.0, 1.0, 0.0));
            matView = mat * matView;
        }
        else if (GLFW_KEY_RIGHT == key) {
            // pan right, rotate around Y, CW
            mat = glm::rotate(glm::radians(angleStep), glm::vec3(0.0, 1.0, 0.0));
            matView = mat * matView;
        }
        if (GLFW_KEY_UP == key) {
            // tilt up, rotate around X, CCW
            mat = glm::rotate(glm::radians(-angleStep), glm::vec3(1.0, 0.0, 0.0));
            matView = mat * matView;
        } if (GLFW_KEY_DOWN == key) {
            // tilt down, rotate around X, CW
            mat = glm::rotate(glm::radians(angleStep), glm::vec3(1.0, 0.0, 0.0));
            matView = mat * matView;
        }
        if ((GLFW_KEY_KP_ADD == key) ||
            (GLFW_KEY_EQUAL == key) && (modes & GLFW_MOD_SHIFT)) {
            // zoom in, move along -Z
            mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, transStep));
            matView = mat * matView;
        }
        else if ((GLFW_KEY_KP_SUBTRACT == key) || (GLFW_KEY_MINUS == key)) {
            // std::cout << "keypad - pressed" << std::endl;
            // zoom out, move along -Z
            mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -transStep));
            matView = mat * matView;
        }
        if (GLFW_KEY_R == key) {
            // reset
            matView = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
            matModelRoot = glm::mat4(1.0f);
        }
    }

    //glm::mat4 mat_scale = glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
    //glm::mat4 mat_rot_y = glm::rotate(glm::radians(rot_y), glm::vec3(0.0f, 1.0f, 0.0f));
    //glm::mat4 mat_rot_x = glm::rotate(glm::radians(rot_x), glm::vec3(1.0f, 0.0f, 0.0f));

    ////glm::mat4 mat_modelview = mat_rot_x * mat_rot_y * mat_scale;
    //matRoot = mat_rot_x*mat_rot_y*mat_scale;

    GLuint modelview_loc = glGetUniformLocation(shader.program, "modelview");
    glUniformMatrix4fv(modelview_loc, 1, GL_FALSE, &matModelRoot[0][0]);
}

GLuint initShader(std::string pathVert, std::string pathFrag)
{
    shader.read_source(pathVert.c_str(), pathFrag.c_str());

    shader.compile();
    glUseProgram(shader.program);
    return shader.program;
}



/*
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
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
*/

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

    glDisable(GL_CULL_FACE);





    // for both VSCode and Visual Studio
    //initShader("shaders/colour.frag", "shaders/colour.vert");
    initShader("shaders/blinn.vert", "shaders/blinn.frag");

    // you are expected to add lines similar to the two lines to create the view and projection matrix

// set the eye at (0, 0, 5), looking at the centre of the world
// try to change the eye position
    matView = glm::lookAt(ViewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    // set the Y field of view angle to 60 degrees, width/height ratio to 1.0, and a near plane of 3.5, far plane of 6.5
    // try to play with the FoV
    matProj = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 100.0f);


    // Meshes
    //std::shared_ptr<Mesh> cube = std::make_shared<Mesh>();
    //cube->init("models/cube.obj", shader.program);

    std::shared_ptr<Mesh> teapot = std::make_shared<Mesh>();
    teapot->init("models/teapot.obj", shader.program);

    std::shared_ptr<Mesh> skull = std::make_shared<Mesh>();
    skull->init("models/planet.obj", shader.program);



    //Nodes
    std::shared_ptr<Node> scene = std::make_shared<Node>();
    std::shared_ptr<Node> teapotNode = std::make_shared<Node>();
    //std::shared_ptr<Node> teapotNode2 = std::make_shared<Node>();
    //std::shared_ptr<Node> teapotNode3 = std::make_shared<Node>();
    //std::shared_ptr<Node> cubeNode = std::make_shared<Node>();
    //std::shared_ptr<Node> cubeNode2 = std::make_shared<Node>();
    //std::shared_ptr<Node> cubeNode3 = std::make_shared<Node>();
    std::shared_ptr<Node> skullNode = std::make_shared<Node>();



    // Build the tree
    teapotNode->addMesh(teapot);
    //teapotNode2->addMesh(teapot);
    //teapotNode3->addMesh(teapot);
    //cubeNode->addMesh(cube);
    //cubeNode2->addMesh(cube);
    //cubeNode3->addMesh(cube);

    skullNode->addMesh(skull);



  //  cubeNode->addChild(teapotNode, glm::translate(glm::vec3(-2.0f, 1.0f, 0.0f)));
//    cubeNode->addChild(teapotNode2, glm::translate(glm::vec3(2.0f, 1.0f, 0.0f)));
   // cubeNode->addChild(skullNode, glm::translate(glm::vec3(0.0f, 1.0f, 0.0f)), glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));
    //cubeNode->addChild(cubeNode2, glm::translate(glm::vec3(2.0f, 0.0f, 0.0f)));
    //cubeNode->addChild(cubeNode3, glm::translate(glm::vec3(-2.0f, 0.0f, 0.0f)));

    // Add the tree to the world space
    scene->addChild(teapotNode, glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));

    //initTriangle();



    
    // setting the background colour, you can change the value
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    
    //makew the models a wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);

    // setting the event loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader.program);

        GLuint modelLoc = glGetUniformLocation(shader.program, "model");
        GLuint viewLoc = glGetUniformLocation(shader.program, "view");
        GLuint projLoc = glGetUniformLocation(shader.program, "projection");

        GLuint lightLoc = glGetUniformLocation(shader.program, "lightPos");
        GLuint viewPosLoc = glGetUniformLocation(shader.program, "viewPos");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &matModelRoot[0][0]);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &matView[0][0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &matProj[0][0]);

        glUniform3fv(lightLoc, 1, &lightPos[0]);
        glUniform3fv(viewPosLoc, 1, &ViewPos[0]);

        scene->draw(matModelRoot, matView, matProj);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
