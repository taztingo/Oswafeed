#pragma once
#include <vector>

#include "Point.h"
#include "Dimension.h"
#include "glad/glad.h"

class Rect
{
	Point topLeft;
	Point bottomRight;
	float z = 0.0f;

public:
    Rect();
	Rect(const Point& topLeft, const Point& bottomRight, float z);
    void move(const Point& vector);
    void resize(const Dimension& dimension);
	std::vector<GLfloat> getVertices();
    std::vector<GLuint> getIndices();
};

Rect::Rect()
{

}

Rect::Rect(const Point& topLeft, const Point& bottomRight, float z) : 
	topLeft(topLeft), bottomRight(bottomRight), z(z)
{

}

std::vector<GLfloat> Rect::getVertices()
{
	std::vector<GLfloat> vertices;
	const float unit = 1.0f / 100.0f;

    // Top right
    vertices.push_back(bottomRight.x * unit);
    vertices.push_back(topLeft.y * unit);
    vertices.push_back(z);

    // Bottom right
    vertices.push_back(bottomRight.x * unit);
    vertices.push_back(bottomRight.y * unit);
    vertices.push_back(z);

    // Bottom left
    vertices.push_back(topLeft.x * unit);
    vertices.push_back(bottomRight.y * unit);
    vertices.push_back(z);

    // Top left
    vertices.push_back(topLeft.x * unit);
    vertices.push_back(topLeft.y * unit);
    vertices.push_back(z);
    
    return std::move(vertices);
}

std::vector<GLuint> Rect::getIndices()
{
    std::vector<GLuint> indices{ 0, 1, 3, 1, 2, 3 };
    return std::move(indices);
}

void Rect::move(const Point& vector)
{
    topLeft.x += vector.x;
    topLeft.y += vector.y;
    bottomRight.x += vector.x;
    bottomRight.y += vector.y;
}

void Rect::resize(const Dimension& dimension)
{
    bottomRight.x = topLeft.x + dimension.width;
    bottomRight.y = topLeft.y + dimension.height;
}