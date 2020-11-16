#pragma once

#include <string>
#include "Image.h"

class Item
{
	std::string name;
	std::string description;
	Image image;

public:
	Item(const std::string& name, const std::string& description, Image& image);
	std::string& getName();
	std::string& getDescription();
};