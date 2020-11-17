#include <iostream>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Oswafeed/Shader.h"
#include "Oswafeed/Rect.h"
#include "Oswafeed/ItemService.h"
#include "Oswafeed/Item.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb.h"

/*void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        std::cout << "Pressed left key" << "\n";
    }
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        std::cout << "Pressed right key" << "\n";
    }
}

void initialize()
{
    if (!glfwInit())
    {
        return;
    }

    glfwSetErrorCallback(error_callback);


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Oswafeed", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);


    std::vector<GLfloat> vertices;
    int rects = 2;
    float unit = 1 / 10.0f;
    float rectLengthUnits = 1;
    float rectHeightUnits = 1;
    float rectLength = unit * rectLengthUnits;
    float rectHeight = unit * rectHeightUnits;
    float padding = unit * 1;
    float topPadding = 1 - (3 * unit);

    //std::vector<Rect> rects;
    //for (int i = 0; i < rects; i++)
    //{
    //
    //}

    float xLocation = -1 + padding;
    for (int i = 0; i < rects; i++) {
        // Top right
        vertices.push_back(xLocation + rectLength);
        vertices.push_back(topPadding);
        vertices.push_back(0.1f);

        // Bottom right
        vertices.push_back(xLocation + rectLength);
        vertices.push_back(topPadding + rectHeight);
        vertices.push_back(0.1f);

        // Bottom left
        vertices.push_back(xLocation);
        vertices.push_back(topPadding + rectHeight);
        vertices.push_back(0.1f);

        // Top left
        vertices.push_back(xLocation);
        vertices.push_back(topPadding);
        vertices.push_back(0.1f);
        xLocation += rectLength + padding;
    }

    std::vector<GLuint> indices;
    for (int i = 0; i < rects; i++)
    {
        int offset = i * 4;
        indices.push_back(offset);
        indices.push_back(offset + 1);
        indices.push_back(offset + 3);

        indices.push_back(offset + 1);
        indices.push_back(offset + 2);
        indices.push_back(offset + 3);
    }

    auto rectShader = Shader("shaders/simple.vs", "shaders/simple.fs");
    auto bgShader = Shader("shaders/bg.vs", "shaders/bg.fs");
    rectShader.compile();
    bgShader.compile();
    
    // Create the background image
    // First step is attaching the texture image to the bound texture

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int imageWidth, imageHeight, imageChannels;
    unsigned char* data = stbi_load("background-compress.jpg", &imageWidth, &imageHeight, &imageChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Unable to load image\n";
    }
    stbi_image_free(data);

    // Create the rect for the background image
    //////////////////////////////////
    // Top right
    vertices.push_back(1.0f);
    vertices.push_back(1.0f);
    vertices.push_back(0.0f);
    // Bottom right
    vertices.push_back(-1.0f);
    vertices.push_back(1.0f);
    vertices.push_back(0.0f);
    // Bottom left
    vertices.push_back(-1.0f);
    vertices.push_back(-1.0f);
    vertices.push_back(0.0f);
    // Top left
    vertices.push_back(1.0f);
    vertices.push_back(-1.0f);
    vertices.push_back(0.0f);

    int offset = rects * 4;
    indices.push_back(offset);
    indices.push_back(offset + 1);
    indices.push_back(offset + 3);

    indices.push_back(offset + 1);
    indices.push_back(offset + 2);
    indices.push_back(offset + 3);
    //////////////////////////////////

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Copy the vertices into the vertex buffer
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

    // Copy the indices in an element buffer for OpenGL
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        // Logic
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        
        bgShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(rects * 6 * sizeof(GLuint)));

        rectShader.use();
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawElements(GL_TRIANGLES, (rects) * 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}*/

void test()
{
    ItemService service;
    service.update();
    for (auto& item : service.getItems())
    {
        std::cout << item->getName() << "\n";
        std::cout << item->getDescription() << "\n";
        std::cout << "------------\n";
    }
}

int main()
{
    test();
    std::string a;
    std::cin >> a;
    //initialize();
    return 0;
}
