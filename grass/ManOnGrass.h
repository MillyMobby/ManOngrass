#pragma once
#include "Shader.h"
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
#include "Vec2f.h"

struct WindowSize {

public:

    float currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f;

    WindowSize() { isChanged = false; width = 1000; height = 625; }

    bool isChanged;
    int width;
    int height;
   
};


class ManOnGrass
{  
    //WINDOW
    GLFWwindow* _window = nullptr;
    GLuint _shaderProgram = -1;
    WindowSize _windowSize;
    Shader bg,man;

    //TEXTURE
    unsigned char* _image;
    std::string _imagePath;
    GLuint _texBG, _texture_man;
    int widthBG, widthMan;
    int heightBG, heightMan, numPerRow;
    float spriteWidth, spriteHeight;
    int _channels;
    int spriteSheetWidth = 25, spriteSheetHeight = 45;
    GLint _wrapS, _wrapT, _wrapR, _minFilter, _magFilter;

    //RECTANGLES
    unsigned int VBO_bg, VAO_bg, EBO_bg;
    unsigned int VBO_man, VAO_man, EBO_man;
    float pos_X = -1.0f;

    //ANIMATION
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f;
    float spriteInd = 14;
    
    
    bool flip = false;
    

public:

    void calculateSpriteInfo();
    void startAnimation();
    bool Init();
    bool Clean();
    void processInput();
    void initBackGround();
    void walk(float posX, float posY, int currentFrame);
    void initTexture_man();

    static void frameBufferSizeCB(GLFWwindow* window, int width, int height);


};
