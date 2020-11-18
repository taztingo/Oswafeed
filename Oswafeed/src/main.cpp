#include <iostream>
#include <vector>

#include "Oswafeed/Oswafeed.h"

void initialize()
{



    // Create the background image
    // First step is attaching the texture image to the bound texture

    /*unsigned int texture;
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
    indices.push_back(offset + 3);*/
    //////////////////////////////////

    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Copy the indices in an element buffer for OpenGL
    
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    

    //Loop logic

        //bgShader.use();
        //glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(rects * 6 * sizeof(GLuint)));

        //rectShader.use();
        //glBindTexture(GL_TEXTURE_2D, texture);
        //glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, (rects) * 6, GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0);
    // Loop logic
}


int main()
{
    Oswafeed feed;
    int width = 1920;
    int height = 1080;
    std::string name = "Oswafeed";
    feed.initialize(width, height, name);
    feed.start();
    return 0;
}
