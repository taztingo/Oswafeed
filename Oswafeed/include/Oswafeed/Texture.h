#pragma once

#include <string>
#include <vector>

class Texture
{
	unsigned int m_renderId;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_width;
	int m_height;
	int m_bpp;

public:
	Texture(const std::string& path);
	Texture(const std::vector<unsigned char>& imageData);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;
	int getWidth() const;
	int getHeight() const;

};