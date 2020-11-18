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

void Rect::getVertices(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices)
{
    const float unit = .1;

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

    int index = (vertices.size() / 3) - 4;
    indices.push_back(index + 0);
    indices.push_back(index + 1);
    indices.push_back(index + 3);
    indices.push_back(index + 1);
    indices.push_back(index + 2);
    indices.push_back(index + 3);
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

Point& Rect::getTopLeft()
{
    return topLeft;
}

Point& Rect::getBottomRight()
{
    return bottomRight;
}