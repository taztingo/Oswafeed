#pragma once
#include <vector>
#include "glad/glad.h"
#include "Oswafeed/Point.h"

struct Dimension;

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