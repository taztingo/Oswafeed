#pragma once

class VertexArray;
class Shader;


#include "Oswafeed/IndexBuffer.h"
#include "Oswafeed/Texture.h"
//class IndexBuffer;
//class Texture;

struct Renderable
{
	Renderable(unsigned int offset, unsigned int count, const Texture& texture)
		: offset(offset), count(count), texture(texture) {};
	unsigned int offset;
	unsigned int count;
	const Texture texture;
};

class Renderer
{
public:
	Renderer();

	void clear() const;
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void draw(const VertexArray& va, const IndexBuffer& ib, const Renderable& rb, const Shader& shader) const;

};