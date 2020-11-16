#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include <iostream>
#include <fstream>

class Shader
{
    GLuint shader;
    std::string vertexPath;
    std::string fragPath;

    GLuint compileShader(const std::string& filepath, int type);

public:
    Shader(const std::string& vertexShader, const std::string& fragmentShader);
    Shader() = delete;
    ~Shader() = default;
    bool compile();
    void use();
};

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
    : vertexPath(vertexShader), fragPath(fragmentShader), shader(0)
{
}

bool Shader::compile()
{
    auto vertexShader = compileShader(vertexPath, GL_VERTEX_SHADER);
    auto fragmentShader = compileShader(fragPath, GL_FRAGMENT_SHADER);
    if (!vertexShader || !fragmentShader)
    {
        std::cout << "Unable to create both shaders\n";
        return false;
    }

    shader = glCreateProgram();
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    glLinkProgram(shader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Failed to create fragment shader: " << infoLog << std::endl;
        return false;
    }

    return true;
}

void Shader::use()
{
    glUseProgram(shader);
}

GLuint Shader::compileShader(const std::string& filepath, int type)
{
    std::ifstream t(filepath);
    std::string input((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    const char* code = input.c_str();

    GLuint vertexShader = glCreateShader(type);
    glShaderSource(vertexShader, 1, &code, NULL);
    glCompileShader(vertexShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Failed to create vertex shader: " << infoLog << std::endl;
        return 0;
    }

    return vertexShader;
}