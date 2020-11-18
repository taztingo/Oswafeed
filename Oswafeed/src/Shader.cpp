#include <iostream>
#include <fstream>
#include "glad/glad.h"
#include "Oswafeed/Shader.h"

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
    : m_vertexPath(vertexShader), m_fragPath(fragmentShader), m_renderId(0)
{
    compile();
}

bool Shader::compile()
{
    auto vertexShader = compileShader(m_vertexPath, GL_VERTEX_SHADER);
    auto fragmentShader = compileShader(m_fragPath, GL_FRAGMENT_SHADER);
    if (!vertexShader || !fragmentShader)
    {
        std::cout << "Unable to create both shaders\n";
        return false;
    }

    m_renderId = glCreateProgram();
    glAttachShader(m_renderId, vertexShader);
    glAttachShader(m_renderId, fragmentShader);
    glLinkProgram(m_renderId);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int success;
    glGetProgramiv(m_renderId, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_renderId, 512, NULL, infoLog);
        std::cout << "Unable to compile shader: " << infoLog << "\n";
        return false;
    }

    return true;
}

unsigned int Shader::compileShader(const std::string& filepath, int type)
{
    std::ifstream t(filepath);
    std::string input((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    const char* code = input.c_str();

    unsigned int vertexShader = glCreateShader(type);
    glShaderSource(vertexShader, 1, &code, nullptr);
    glCompileShader(vertexShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "Failed to create vertex shader: " << infoLog << std::endl;
        return 0;
    }

    return vertexShader;
}


Shader::~Shader()
{
    glDeleteProgram(m_renderId);
}

void Shader::bind() const
{
    glUseProgram(m_renderId);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::setUniform1i(const std::string& name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform1f(const std::string& name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

int Shader::getUniformLocation(const std::string& name)
{
    int location = -1;
    if (m_uniformCache.find(name) == m_uniformCache.end())
    {
        location = glGetUniformLocation(m_renderId, name.c_str());
        if (location == -1)
        {
            std::cout << "Uniform " << name << " does not exist.\n";
        }

        m_uniformCache[name] = location;
    }
    
    return m_uniformCache[name];
}
