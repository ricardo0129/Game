#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"       
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/string_cast.hpp"
#include <iostream>
#include "shader.h"
#include "render.h"
#include "camera.h"
#include "object.h"
#include <stdio.h>     
#include <stdlib.h>    
#include <time.h>       
#include <unistd.h>
#include "physics.h"
#include "projectile.h"
#include "force.h"

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const unsigned int FPS=60;

glm::vec3 cameraPos   = glm::vec3(-10.0f, 0.0f,  0.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
float yaw = 0.0f;
float lastX =  800.0f / 2.0;
float lastY =  800.0 / 2.0;
float pitch = 0.0f;
bool firstMouse = true;

glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 300.0f);
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    
    glEnable(GL_DEPTH_TEST);  

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
    glm::vec3( 4.0f,  4.0f,  4.0f), 
    };
    srand (time(NULL));

  /* generate secret number between 1 and 10: */
    float iSecret = rand();
    float verts[600];
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            float height =static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            verts[i*60+j*6+0]=j*1.0/10.0;
            verts[i*60+j*6+1]=height;
            verts[i*60+j*6+2]=i*1.0/10.0;
            verts[i*60+j*6+3]=1.0-height;
            verts[i*60+j*6+4]=1.0-height;
            verts[i*60+j*6+5]=1.0-height;
        }
    }

    unsigned int indices[486];
    unsigned int pre[]={0,1,10,1,10,11};
    for(int i=0;i<81;i++)
    {
        for(int j=0;j<6;j++)
        {
            indices[i*6+j]=pre[j]+i;
        }
    }

    Object a(vertices,glm::vec3( 1.0f,  1.0f,  1.0f));
    Camera cam(800,800
    );

 
     
    Shader modelShader("vertex.shader", "fragment.shader");
    Render terrain(verts, sizeof(verts), indices, sizeof(indices));
    Render cube(vertices, sizeof(vertices));
    Gravity FGravity(glm::vec3(0.0f,-9.8f,0.0f));
    Drag FDrag(0.7f,0.7f);
    glm::vec3 start(1.0f,1.0f,1.0f);
    AnchorSpring FSpring(&start,25.0f,1.0f);
    ForceRegisters forces;
    forces.add(&a, &FGravity);
    //forces.add(&a, &FDrag);
    forces.add(&a, &FSpring);


    modelShader.use();
    unsigned int modelM = modelShader.uniformLocation("model");
    unsigned int viewM = modelShader.uniformLocation("view");
    unsigned int projectionM = modelShader.uniformLocation("projection");
    
    float counter=0.0f;
    glm::mat4 model = a.getModel();
    float startime=glfwGetTime();
    int frames=0;
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        glClearColor(0.37f, 0.38f, 0.48f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		modelShader.use();
        forces.updateForces(1.0/60.0);
        counter+=0.1f;
        
        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);        
        modelShader.uniformMat4(viewM, view);
        modelShader.uniformMat4(projectionM, projection);

        cout<<"pos="<<glm::to_string(a.getPos())<<endl;
        cout<<"velocity="<<glm::to_string(a.getVelocity())<<endl;
        cout<<"acceleration="<<glm::to_string(a.getAcceleration())<<endl;
        frames++;
        if((glfwGetTime()-startime)>=1.0)
        {
            cout<<frames<<endl;
            frames=0;
            startime=glfwGetTime();
        }

        model = a.getModel();
        cube.bind(); 
        modelShader.uniformMat4(modelM, glm::translate(model, a.getPos()));
        Physics::update(&a);
        //a.setVelocity(engine.updateVelocity(a.getVelocity(),a.getAcceleration()));
        cube.draw();

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-100, -50, -100));
        model = glm::scale(trans, glm::vec3(400, 40, 400));  
        modelShader.uniformMat4(modelM, model);
        terrain.bind();
        terrain.drawElements();
        a.clearForce();
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
    float cameraSpeed = 0.1f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}