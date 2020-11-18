#include <vector>
#include <iostream>
#include "Oswafeed/Scroller.h"
#include "Oswafeed/Item.h"
#include "Oswafeed/Dimension.h"

Scroller::Scroller()
{
}

void Scroller::add(std::unique_ptr<Item> item)
{
    //float unit = 1 / 10.0f;

    float xLocation = rect.getTopLeft().x;

    if (items.size() > 0)
    {
        xLocation = items[items.size() - 1]->getRect().getBottomRight().x + itemPadding;
    }

    Point p(xLocation, rect.getTopLeft().y);
    Dimension d(1.0, rect.getTopLeft().y -  rect.getBottomRight().y);
    item->getRect().move(p);
    item->getRect().resize(d);
    items.push_back(std::move(item));
}

void Scroller::clear()
{
	items.clear();
	selected = 0;
}

void Scroller::moveLeft()
{
	if (selected <= 0)
	{
		return;
	}

	selected -= 1;
}

void Scroller::moveRight()
{
	if (items.size() > 0 && selected < items.size() - 1)
	{
		return;
	}

	selected += 1;
}

void Scroller::render()
{
    vertices.clear();
    indices.clear();

    for (auto& item : items)
    {
        auto& rect = item->getRect();
        rect.getVertices(vertices, indices);
    }

    if (items.size() > 0)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
        glDrawElements(GL_TRIANGLES, items.size() * 6, GL_UNSIGNED_INT, 0);
    }
    
}

void Scroller::move(Point& p)
{
    rect.getTopLeft().x = p.x;
    rect.getTopLeft().y = p.y;
}

void Scroller::resize(Dimension& d)
{
    rect.getBottomRight().x = rect.getTopLeft().x + d.width;
    rect.getBottomRight().y = rect.getTopLeft().y + d.height;
}

void Scroller::initialize(Point& location, Dimension& size)
{
    vertices.reserve(100 * 3);
    indices.reserve(100 * 3);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    move(location);
    resize(size);
}