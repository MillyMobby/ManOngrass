#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
//materiale punta alla texture, ma non la possiede


void Texture::setName(const std::string& name) {
	_name = name;
}

const std::string& Texture::getName() const {
	return _name;
}

void Texture::setTexName(const std::string& texName) {
	_texName = texName;
}

const std::string& Texture::getTexName() {
	return _texName;
}

void Texture::setWrapMode(const GLint& wrapS, const GLint& wrapT, const GLint& wrapR) {
	_wrapS = wrapS;
	_wrapT = wrapT;
	_wrapR = wrapR;
}

void Texture::setFilterMode(const GLint& minFilter, const GLint& magFilter) {
	_minFilter = minFilter;
	_magFilter = magFilter;

}

GLint Texture::getFilter(std::string filter) {
	GLint rv = GL_NEAREST;
	if (filter.compare("GL_NEAREST") == 0) {
		rv = GL_NEAREST;
	}
	else if (filter.compare("GL_LINEAR") == 0) {
		rv = GL_LINEAR;
	}
	else {
		std::cout << "ERRORE:: NON ESISTE QUESTO TIPO DI FILTRO: " << filter << std::endl;
	}

	return rv;
}

void Texture::setMinFilter(const GLint& minFil) {
	_minFilter = minFil;
}
void Texture::setMinFilter(const std::string& minFil) {
	setMinFilter(getFilter(minFil));
}

const GLint& Texture::getMinFilter() const {
	return _minFilter;
}

void Texture::setMagFilter(const GLint& magFil) {
	_magFilter = magFil;
}

void Texture::setMagFilter(const std::string& magFil) {
	setMagFilter(getFilter(magFil));
}

const GLint& Texture::getMagFilter() const {
	return _magFilter;
}

void Texture::setWrapS(const GLint& wrapS) {
	_wrapS = wrapS;
}
void Texture::setWrapS(const std::string& wrapS) {
	setWrapS(getWrap(wrapS));
}

const GLint& Texture::getWrapS() const {
	return _wrapS;
}

void Texture::setWrapT(const GLint& wrapT) {
	_wrapT = wrapT;
}

void Texture::setWrapT(const std::string& wrapT) {
	setWrapT(getWrap(wrapT));
}

const GLint& Texture::getWrapT() const {
	return _wrapT;
}

void Texture::setWrapR(const GLint& wrapR) {
	_wrapR = wrapR;
}

void Texture::setWrapR(const std::string& wrapR) {
	setWrapR(getWrap(wrapR));
}

const GLint& Texture::getWrapR() const {
	return _wrapR;
}

GLint Texture::getWrap(std::string wrap) {
	GLint rv = GL_REPEAT;
	if (wrap.compare("GL_REPEAT") == 0) {
		rv = GL_REPEAT;
	}
	else if (wrap.compare("GL_MIRRORED_REPEAT") == 0) {
		rv = GL_MIRRORED_REPEAT;
	}
	else if (wrap.compare("GL_CLAMP_TO_EDGE") == 0) {
		rv = GL_CLAMP_TO_EDGE;
	}
	else if (wrap.compare("GL_CLAMP_TO_BORDER") == 0) {
		rv = GL_CLAMP_TO_BORDER;
	}
	else if (wrap.compare("GL_MIRROR_CLAMP_TO_EDGE") == 0) {
		rv = GL_MIRROR_CLAMP_TO_EDGE;
	}
	else {
		std::cout << "ERRORE:: NON ESISTE QUESTO TIPO DI WRAP: " << wrap << std::endl;
	}
	return rv;
}

GLsizei Texture::getImageSize() const {
	return _width * _height * _channels;
}

//void Texture::setImagePath(const std::string path) {
//	_imagePath = path;
//}
void Texture::setImagePath(const std::string path) {
	_imagesPaths.push_back(path);
}

const std::string Texture::getImagePath() const {
	return _imagesPaths[0];
}

//void Texture::loadImage() {
//	stbi_set_flip_vertically_on_load(true);
//	
//	_image = stbi_load(_imagePath.c_str(), &_width, &_height, &_channels, 0);
//}

bool Texture::loadImages() {
	bool rv = false;

	for (int i = 0; i < _imagesPaths.size(); ++i) {
		loadImage(_imagesPaths[i]);
		if (_image) {
			if (_imagesPaths.size() == 1) {
				glTexImage2D(_type, 0, _channels > 3 ? GL_RGBA : GL_RGB, _width, _height, 0, _channels > 3 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, _image);
			}
			else {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, _channels > 3 ? GL_RGBA : GL_RGB, _width, _height, 0, _channels > 3 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, _image);
			}
			glGenerateMipmap(_type);
			rv = true;
		}
		else
		{
			rv = false;
			std::cout << "ERRORE::FILE IMMAGINE TEXTURE NON TROVATO " << getImagePath() << std::endl;
		}
		stbi_image_free(_image);
	}
	return rv;
}

void Texture::loadImage(std::string imagePath) {
	if (_type == GL_TEXTURE_CUBE_MAP) {
		stbi_set_flip_vertically_on_load(false);
	}
	else {
		stbi_set_flip_vertically_on_load(true);
	}

	_image = stbi_load(imagePath.c_str(), &_width, &_height, &_channels, 0);
}

bool Texture::initGL() {
	bool rv = false;

	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load("D:/grass.png ", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	return rv;
}

//bool Texture::initGL() {
//	bool rv = false;
//	loadImages();
//	if (_image) {
//		glGenTextures(1, &_textureID);
//		glBindTexture(_type, _textureID);
//
//		glTexParameteri(_type, GL_TEXTURE_WRAP_S, _wrapS);
//		glTexParameteri(_type, GL_TEXTURE_WRAP_T, _wrapT);
//		glTexParameteri(_type, GL_TEXTURE_WRAP_R, _wrapR);
//
//		glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, _minFilter);
//		glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, _magFilter);
//
//		//????
//		glTexImage2D(_type, 0, _channels > 3 ? GL_RGBA : GL_RGB, _width, _height, 0, _channels > 3 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, _image);
//		glGenerateMipmap(_type);
//
//		glBindTexture(_type, 0);
//		rv = true;
//	}
//	else
//	{
//		std::cout << "ERRORE::FILE IMMAGINE TEXTURE NON TROVATO " << getImagePath() << std::endl;
//		return 0;
//	}
//	stbi_image_free(_image);
//	return rv;
//}


void Texture::bind() {
	glBindTexture(_type, _textureID);
}



void Texture::setType(const std::string& type) { // CUBEMAP
	setType(getType(type));
}

void Texture::setType(const GLint& type) { // CUBEMAP
	_type = type;
}


GLint Texture::getType(std::string type) { // CUBEMAP

	GLint rv = GL_TEXTURE_2D;
	if (type.compare("GL_TEXTURE_2D") == 0) {
		rv = GL_TEXTURE_2D;
	}
	else if (type.compare("GL_TEXTURE_CUBE_MAP") == 0) {
		rv = GL_TEXTURE_CUBE_MAP;
	}
	else {
		std::cout << "ERRORE:: NON ESISTE QUESTO TIPO DI TEXTURE O NON E' SUPPORTATA" << std::endl;
	}

	return rv;
}