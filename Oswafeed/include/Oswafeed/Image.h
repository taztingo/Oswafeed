#pragma once

#include <memory>
#include <istream>
#include "Rect.h"


class Image
{
	std::unique_ptr<std::istream> image;
	Rect rect;
public:
	Image(std::unique_ptr<std::istream> image);
};