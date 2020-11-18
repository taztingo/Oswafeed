#pragma once
#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

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
    void use() const;
};