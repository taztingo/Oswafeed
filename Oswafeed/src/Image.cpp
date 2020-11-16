#include "Oswafeed/Image.h"
#include <istream>

Image::Image(std::unique_ptr<std::istream> image)
	: image(std::move(image))
{
}