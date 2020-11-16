#include "Oswafeed/Rect.h"
#include "Oswafeed/Point.h"
#include "Oswafeed/Dimension.h"

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