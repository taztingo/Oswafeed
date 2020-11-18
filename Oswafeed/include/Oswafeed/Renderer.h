#pragma once

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer
{
public:
	Renderer();

	void clear() const;
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};