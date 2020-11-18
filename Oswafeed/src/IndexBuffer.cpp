#include "Oswafeed/IndexBuffer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_count(count)
{
	glGenBuffers(1, &m_renderId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_renderId);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_renderId);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getCount() const
{
	return m_count;
}