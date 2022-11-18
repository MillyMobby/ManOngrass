#pragma once
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>

#include <vector>

class Texture
{

private:
	std::string _name;
	std::string _texName;

	GLint _type;

	unsigned char* _image;

	std::vector<std::string> _imagesPaths; // ha dimensione 1 o 6 in base al tipo

	GLuint _textureID;
	GLint _wrapS, _wrapT, _wrapR, _minFilter, _magFilter;
	int _channels;
	int _width, _height;

public:
	Texture() {};
	~Texture() {}

	void setType(const std::string& type);
	void setType(const GLint& type);
	GLint getType(std::string type);

	void setImagesPats(std::vector<std::string> paths) {
		_imagesPaths = paths;
	}

	void setName(const std::string& name);
	const std::string& getName() const;

	void setTexName(const std::string& texName);
	const std::string& getTexName();

	void setImagePath(const std::string path);
	const std::string getImagePath() const;

	void setMinFilter(const GLint& minFil);
	void setMinFilter(const std::string& minFil);
	const GLint& getMinFilter() const;
	void setMagFilter(const GLint& magFil);
	void setMagFilter(const std::string& magFil);
	const GLint& getMagFilter() const;
	GLint getFilter(std::string filter);
	void setFilterMode(const GLint& minFilter, const GLint& magFilter);

	void setWrapMode(const GLint& wrapS, const GLint& wrapT, const GLint& wrapR);
	void setWrapS(const GLint& wrapS);
	void setWrapS(const std::string& wrapS);
	const GLint& getWrapS() const;
	void setWrapR(const GLint& wrapR);
	void setWrapR(const std::string& wrapR);
	const GLint& getWrapR() const;
	void setWrapT(const GLint& wrapT);
	void setWrapT(const std::string& wrapT);
	const GLint& getWrapT() const;
	GLint getWrap(std::string wrap);
	GLsizei getImageSize() const;

	bool initGL();
	void bind();

private:

	//void loadImage();

	bool loadImages();
	void loadImage(std::string imagePath); //NEW PROVA

};