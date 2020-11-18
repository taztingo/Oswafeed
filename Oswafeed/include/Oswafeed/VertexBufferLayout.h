#pragma once

#include <vector>
#include "glad/glad.h"

struct VertexBufferLayoutElement
{
	/*VertexBufferLayoutElement(unsigned int t, unsigned int c, bool n, unsigned int s)
		: count(c), type(t), normalized(n), size(s) {};*/
	unsigned int type;
	unsigned int count;
	unsigned int normalized;
	unsigned int size;
};

class VertexBufferLayout
{
	std::vector<VertexBufferLayoutElement> m_elements;
	unsigned int m_stride;
public:
	VertexBufferLayout() : m_stride(0) {};

	template<typename T>
	void push(unsigned int count)
	{
		// Not supported
	}

	template<>
	void push<float>(unsigned int count)
	{
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE, sizeof(GLfloat) });
		m_stride += count * sizeof(GLfloat);
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE, sizeof(GLuint) });
		m_stride += count * sizeof(GLuint);
	}

	unsigned int getStride() const { return m_stride; }
	const std::vector<VertexBufferLayoutElement>& getElements() const { return m_elements; }

};