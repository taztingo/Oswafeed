#pragma once
#include <string>
#include <unordered_map>

class Shader
{
    unsigned int m_renderId;
    std::string m_vertexPath;
    std::string m_fragPath;
    std::unordered_map<std::string, int> m_uniformCache;

    unsigned int compileShader(const std::string& shader, int type);
    bool compile();

public:
    Shader(const std::string& vertexPath, const std::string& fragPath);
    ~Shader();
    void bind() const;
    void unbind() const;

    void setUniform1i(const std::string& name, int value);
    void setUniform1f(const std::string& name, float value);
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

    int getUniformLocation(const std::string& name);

};