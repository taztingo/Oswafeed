#pragma once
#include <vector>
#include "Item.h"
#include "Rect.h"

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

void Scroller::add(Item&& item)
{
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