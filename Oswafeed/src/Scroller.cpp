#include <vector>

#include "Oswafeed/Scroller.h"
#include "Oswafeed/Item.h"

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