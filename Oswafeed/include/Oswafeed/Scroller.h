#pragma once
#include <vector>
#include "Oswafeed/Item.h"

class Scroller
{
	int selected = 0;
	std::vector<Item> items;
public:
	Scroller() = default;
	void add(Item&& item);
	void moveLeft();
	void moveRight();
	void clear();
};