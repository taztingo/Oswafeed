#include <iostream>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Oswafeed/Oswafeed.h"
#include "Oswafeed/Dimension.h"
#include "Oswafeed/VertexBuffer.h"
#include "Oswafeed/IndexBuffer.h"
#include "Oswafeed/VertexArray.h"
#include "Oswafeed/VertexBufferLayout.h"
#include "Oswafeed/Renderer.h"
#include "Oswafeed/Texture.h"
#include "Oswafeed/Shader.h"

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
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
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

    Point p(-.7f, .7f);
    Dimension d(1.4f, .2f);
    scroller.initialize(p, d);

    return true;
}

void Oswafeed::start()
{
    // Create the background
    std::vector<GLfloat> vertices = {
        -1.0, 1.0f, 0.0f, 1.0f,   // Top left
        -1.0f, -1.0f, 0.0f, 0.0f,  // Bottom left
        1.0f, -1.0f, 1.0f, 0.0,   // Bottom right
        1.0f, 1.0f, 1.0f, 1.0f     // Top right
    };

    std::vector<GLuint> indices = {
        0, 1, 2,
        2, 3, 0
    };

    std::vector<std::unique_ptr<Renderable>> renderables;
    auto backgroundTexture = Texture("resources/background-compress.jpg");
    auto background = std::make_unique<Renderable>(0, 6, backgroundTexture);
    renderables.push_back(std::move(background));
    /////////////////////////////////

    // We aren't always guaranteed to have an update
    service.update();
    if (service.isUpdated())
    {
        for (auto& item : service.getItems())
        {
            scroller.add(std::move(item));
        }
    }
    scroller.render();

    for (auto& item : scroller.getItems())
    {
        auto newItem = std::make_unique<Renderable>(indices.size(), 6, item->getTexture());
        item->getRect().getVertices(vertices, indices);
        renderables.push_back(std::move(newItem));
    }



    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_BLEND);

    VertexArray va;

    VertexBuffer vb(&vertices[0], vertices.size() * sizeof(GLfloat));
    // vb(&vertices[0], sizeof(GLfloat) * 4 * 4);
    VertexBufferLayout layout;
    layout.push<GLfloat>(2);
    layout.push<GLfloat>(2);
    va.addBuffer(vb, layout);
    IndexBuffer ib(&indices[0], indices.size());
    //IndexBuffer ib(&indices[0], indices);
    Renderer renderer;
    Shader shader("shaders/simple.vs", "shaders/simple.fs");
    shader.bind();

    //Texture texture("resources/background-compress.jpg");
    //texture.bind(0);
    shader.setUniform1i("u_Texture", 0);

    va.unbind();
    ib.unbind();
    vb.unbind();
    shader.unbind();
    
    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);


        renderer.clear();
        for (auto& renderable : renderables)
        {
            renderer.draw(va, ib, *renderable, shader);
        }
        
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

Oswafeed::Oswafeed() : 
    height(0), width(0), window(0)
{

}