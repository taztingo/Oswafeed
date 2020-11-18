#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Oswafeed/Oswafeed.h"
#include "Oswafeed/Dimension.h"
#include "Oswafeed/VertexBuffer.h"
#include "Oswafeed/IndexBuffer.h"
#include "Oswafeed/VertexArray.h"
#include "Oswafeed/VertexBufferLayout.h"

void Oswafeed::errorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void Oswafeed::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        scroller.moveLeft();
    }
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        scroller.moveRight();
    }
}

bool Oswafeed::initialize(int width, int height, std::string& name)
{
    if (!glfwInit())
    {
        return false;
    }

    this->width = width;
    this->height = height;
    this->name = std::move(name);

    // Not sure how to set this
    //glfwSetErrorCallback(window);


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(this->width, this->height, this->name.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return false;
    }
    glfwSetWindowUserPointer(window, this);
    auto func = [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        static_cast<Oswafeed*>(glfwGetWindowUserPointer(window))->keyCallback(window, key, scancode, action, mods);
    };
    glfwSetKeyCallback(window, func);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    if (!rectShader.compile() || !bgShader.compile())
    {
        return false;
    }

    Point p(-.7f, .7f);
    Dimension d(1.4f, .2f);
    scroller.initialize(p, d);

    return true;
}

void Oswafeed::start()
{
    GLfloat vertices[] = {
        -.5f, .5f, 0.0f,   // Top left
        -.5f, -.5f, 0.0f,  // Bottom left
        .5f, -.5f, 0.0f,   // Bottom right
        .5f, .5f, 0.0f     // Top right
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va;

    VertexBuffer vb(vertices, sizeof(GLfloat) * 4 * 3);
    VertexBufferLayout layout;
    layout.push<GLfloat>(3);
    va.addBuffer(vb, layout);
    IndexBuffer ib(indices, 6);
    
    bool alreadyRan = false;
    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);


        // We aren't always guaranteed to have an update
        //service.update();
        //if (service.isUpdated())
        //{
        //    if (!alreadyRan)
        //    {
        //        alreadyRan = true;
        //        for (auto& item : service.getItems())
        //        {
        //            scroller.add(std::move(item));
        //        }
        //    }
            
        //}

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        rectShader.use();
        va.bind();
        ib.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        //va.unbind();
        //scroller.render();

        // We need to do our render logic here
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

Oswafeed::Oswafeed()
    : rectShader("shaders/simple.vs", "shaders/simple.fs"),
    bgShader("shaders/bg.vs", "shaders/bg.fs")
{

}