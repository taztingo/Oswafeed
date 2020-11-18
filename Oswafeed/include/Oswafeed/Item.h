#pragma once

#include <string>
#include <memory>
#include <istream>
#include "Rect.h"

class Item
{
	std::string name;
	std::string description;
	Rect rect;
	std::unique_ptr<std::istream> image;

public:
	Item(const std::string& name, const std::string& description, std::unique_ptr<std::istream> image);
	std::string& getName();
	std::string& getDescription();
	std::istream& getImage();
	Rect& getRect();
};