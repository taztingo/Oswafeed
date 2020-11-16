#pragma once

#include <string>
#include <memory>
#include <istream>
#include "Rect.h"
#include "Point.h"
#include "Dimension.h"

class Image
{
	std::unique_ptr<std::istream> image;
	Rect rect;
public:
	Image(std::unique_ptr<std::istream> image);
};

Image::Image(std::unique_ptr<std::istream> image)
	: image(std::move(image))
{
}