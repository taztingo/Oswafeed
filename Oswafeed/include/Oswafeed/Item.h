#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Oswafeed/Rect.h"
#include "Oswafeed/Texture.h"

class Item
{
	std::string name;
	std::string description;
	Rect rect;
	Texture texture;

public:
	Item(const std::string& name, const std::string& description, const std::vector<unsigned char>& imageData);
	std::string& getName();
	std::string& getDescription();
	const Texture& getTexture() const;
	Rect& getRect();
};