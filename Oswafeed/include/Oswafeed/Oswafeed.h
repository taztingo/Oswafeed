#pragma once

#include <string>
#include "Oswafeed/ItemService.h"
#include "Oswafeed/Scroller.h"
#include "Oswafeed/Shader.h"
struct GLFWwindow;

class Oswafeed
{
	GLFWwindow* window;
	int width;
	int height;
	std::string name;
	ItemService service;
	Scroller scroller;
	Shader rectShader;
	Shader bgShader;
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	void errorCallback(int error, const char* description);
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
public:
	Oswafeed();
	bool initialize(int width, int height, std::string& name);
	void start();
};