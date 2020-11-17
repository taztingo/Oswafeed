#pragma once

class IndexBuffer
{
	unsigned int m_renderId;
	unsigned int m_count;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	unsigned int getCount() const;
};