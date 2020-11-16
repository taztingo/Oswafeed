#include "Oswafeed/Item.h"

Item::Item(const std::string& name, const std::string& description, Image& image) :
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

