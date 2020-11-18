#pragma once

class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
	unsigned int m_renderId;
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void bind() const;
	void unbind() const;
};