#include "Oswafeed/Renderer.h"
#include "Oswafeed/VertexArray.h"
#include "Oswafeed/IndexBuffer.h"
#include "Oswafeed/Shader.h"

Renderer::Renderer()
{

}

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.use();
    va.bind();
    ib.bind();
    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}
