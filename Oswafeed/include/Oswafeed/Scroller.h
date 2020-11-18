#pragma once
#include <vector>
#include <memory>
#include "Oswafeed/Item.h"
#include "Oswafeed/Rect.h"

class Item;
struct Dimension;

class Scroller
{
	int selected = 0;
	std::vector<std::unique_ptr<Item>> items;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	Rect rect;
	float itemPadding = 1.0f;

public:
	Scroller();
	void add(std::unique_ptr<Item> item);
	void moveLeft();
	void moveRight();
	void clear();
	void render();
	void move(Point& newLocation);
	void resize(Dimension& d);
	void initialize(Point& location, Dimension& size);
};