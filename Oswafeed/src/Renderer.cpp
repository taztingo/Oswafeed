#include "Oswafeed/Renderer.h"
#include "Oswafeed/VertexArray.h"
#include "Oswafeed/IndexBuffer.h"
#include "Oswafeed/Shader.h"
#include "glad/glad.h"

Renderer::Renderer()
{

}

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.bind();
    va.bind();
    ib.bind();
    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Renderable& rb, const Shader& shader) const
{
    shader.bind();
    va.bind();
    ib.bind();
    rb.texture.bind(0);
    glDrawElements(GL_TRIANGLES, rb.count, GL_UNSIGNED_INT, (const void*)(rb.offset * sizeof(GLuint)));
}
