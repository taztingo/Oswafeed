#include "Oswafeed/Item.h"


Item::Item(const std::string& name, const std::string& description, std::unique_ptr<std::istream> image) :
	name(name), description(description), image(std::move(image))
{

}

std::string& Item::getName()
{
	return name;
}

std::string& Item::getDescription()
{
	return description;
}

std::istream& Item::getImage()
{
	return *image;
}

Rect& Item::getRect()
{
	return rect;
}
