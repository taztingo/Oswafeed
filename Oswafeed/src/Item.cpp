#include "Oswafeed/Item.h"
#include <vector>


Item::Item(const std::string& name, const std::string& description, const std::vector<unsigned char>& imageData) :
	name(name), description(description), texture(imageData)
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

const Texture& Item::getTexture() const
{
	return texture;
}

Rect& Item::getRect()
{
	return rect;
}
