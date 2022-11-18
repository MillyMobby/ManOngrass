#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb_image.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include"Material.h"
#include "Vec4f.h"




using namespace std;

class Viewer
{

private:

	string title = "";
	int width = 0;
	int height = 0;
	Vec4f backgroundColor = Vec4f();

	// finestra
	GLFWwindow* _window = nullptr;

public:
	Viewer() {};
	~Viewer() { delete _window; };
	Material bg;
	unsigned char* _image;
	std::string _imagePath;
	/*Object2D o;
	Object2D s;*/
	unsigned int texture1;
	GLint _wrapS, _wrapT, _wrapR, _minFilter, _magFilter;
	unsigned int VBO, VAO, EBO;
	int _channels;


	void setTitle(string t);
	void setBackgroundColor(float r, float g, float b, float a);
	void setBackgroundColor(Vec4f vecColor);
	void setWidth(int w);
	void setHeight(int h);
	void setBGImage();
	//Texture getTextureBG();
	void Run();

private:
	bool Init();
	void Clean();
};
