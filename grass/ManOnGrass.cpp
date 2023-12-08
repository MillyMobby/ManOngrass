#include "ManOnGrass.h"

void main() {
	ManOnGrass manOnGrass;
	manOnGrass.startAnimation();
}


void ManOnGrass::startAnimation() {
	Init();
	bg.setName("background");
	bg.setVShader("bg.vert");
	bg.setFShader("bg.frag");
	/*std::cout << "path1 " << bg.getVShader();
	std::cout << "path2 " << bg.getFShader();*/

	bg.buildMaterial();
	std::cout << "Vertex shader " << bg.getVShader() << std::endl;
	std::cout << "Fragment shader " << bg.getFShader() << std::endl;

	initBackGround();
	initTexture_man();
	
	while (!glfwWindowShouldClose(_window)) {
	
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		float velocity = 2.5f * deltaTime;
		if (spriteInd > 14 || spriteInd < 0) { spriteInd = 0; }
		
		
		if (pos_X + 2*spriteWidth < 1 && flip == false) {
			pos_X = pos_X + velocity/5;
			spriteInd += 2 * velocity;flip = false;
		}
		else {
			
			flip = true;
		}
		if (flip == true && pos_X > -1) {
			//if (spriteInd > 14 || spriteInd < 0) { spriteInd = 0; }
			//std::cout << "sprite ind = " << spriteInd;
			pos_X = pos_X - velocity/5;
			spriteInd += 2 * velocity;
			//std::cout << " vado a sinistraaa \n"; 
		}
		else flip = false;
		
		//glUniform1f(glGetUniformLocation(bg.getShaderProgram(), "SpriteTraslationX"),);
		walk(pos_X, -0.75f, spriteInd);
		
		processInput();

		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//bind
		glBindTexture(GL_TEXTURE_2D, _texBG);

		glUseProgram(bg.getShaderProgram());
		glBindVertexArray(VAO_bg);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindTexture(GL_TEXTURE_2D, _texture_man);
		glBindVertexArray(VAO_man);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_POINTS, 0, 1);


		glfwSwapBuffers(_window);
		glfwPollEvents();

	}

	Clean();

}

void ManOnGrass::initBackGround() {
	float vertices[] = {
		// positions          // colors           // texture coords
		 1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glGenVertexArrays(1, &VAO_bg);
	glGenBuffers(1, &VBO_bg);
	glGenBuffers(1, &EBO_bg);

	glBindVertexArray(VAO_bg);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_bg);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_bg);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	
	stbi_set_flip_vertically_on_load(true);
	_image = stbi_load("erba.png", &_windowSize.width, &_windowSize.height, &_channels, 0);

	//init Textures
	if (_image) {
		
		glGenTextures(1, &_texBG);
		glBindTexture(GL_TEXTURE_2D, _texBG);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, _channels > 3 ? GL_RGBA : GL_RGB, _windowSize.width, _windowSize.height, 0, _channels > 3 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, _image);
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(_image);


}

void ManOnGrass::calculateSpriteInfo() {
	spriteWidth = float(spriteSheetWidth) / widthMan; //texture x
	spriteHeight = float(spriteSheetHeight) / heightMan;//texture y
	numPerRow = widthMan / spriteSheetWidth;
	
}

void ManOnGrass::walk(float posX, float posY, int currentFrame) {

	const float tx = (currentFrame % numPerRow) * spriteWidth;
	const float ty = (2 - (currentFrame / numPerRow)) * spriteHeight;

	std::vector<Vec2f> textureCoords = {
			

			Vec2f(tx, ty + spriteHeight),					// top right											
			Vec2f(tx, ty),									// bottom right	
			Vec2f(tx + spriteWidth, ty),					// bottom left
			Vec2f(tx + spriteWidth, ty + spriteHeight)		// top left 

	};
	//SE DEVE TORNARE INDIETRO LI DISEGNA AL CONTRARIO
	if (flip == false) std::reverse(textureCoords.begin(), textureCoords.end());
	
	float vertices[] = {
		// positions						// colors				// texture coords

		posX + 0.2, -0.75f + 0.6,	0.0f,		1.0f, 1.0f, 0.0f,		textureCoords[0].x ,textureCoords[0].y,		// top right											
		posX + 0.2, -0.75f,		0.0f,		1.0f, 0.0f, 0.0f,		textureCoords[1].x ,textureCoords[1].y,						// bottom right	
		posX,		-0.75f,		0.0f,		0.0f, 1.0f, 0.0f,		textureCoords[2].x ,textureCoords[2].y,				// bottom left
		posX,		-0.75f + 0.6,	0.0f,		0.0f, 0.0f, 1.0f,		textureCoords[3].x ,textureCoords[3].y		// top left 

	};


	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};


	glGenVertexArrays(1, &VAO_man);
	glGenBuffers(1, &VBO_man);
	glGenBuffers(1, &EBO_man);

	glBindVertexArray(VAO_man);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_man);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_man);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

void ManOnGrass::initTexture_man() {
	stbi_set_flip_vertically_on_load(true);
	_image = stbi_load("man.png", &widthBG, &heightBG, &_channels, 0);

	widthMan = widthBG;
	heightMan = heightBG;
	std::cout << "larghezza" << widthMan;
	std::cout << "altezza " << heightMan;

	if (_image) {

		glGenTextures(1, &_texture_man);
		glBindTexture(GL_TEXTURE_2D, _texture_man);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, _channels > 3 ? GL_RGBA : GL_RGB, widthBG, heightBG, 0, _channels > 3 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, _image);
		glGenerateMipmap(GL_TEXTURE_2D);


	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	calculateSpriteInfo();
	stbi_image_free(_image);
}

void ManOnGrass::processInput() {


	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(_window, true);
	}


}


bool ManOnGrass::Clean() {
	glfwTerminate();

	return true;
}

void ManOnGrass::frameBufferSizeCB(GLFWwindow* window, int width, int height) {
	if (window != nullptr) {
		glViewport(0, 0, width, height);
		WindowSize* windowSize = (WindowSize*)glfwGetWindowUserPointer(window);
		if (windowSize != nullptr) {
			windowSize->width = width;
			windowSize->height = height;
			windowSize->isChanged = true;
		}
	}
}

bool ManOnGrass::Init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_windowSize.isChanged = false;

	_window = glfwCreateWindow(_windowSize.width, _windowSize.height, "man on grass", NULL, NULL);

	glfwMakeContextCurrent(_window);
	if (_window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glfwSetFramebufferSizeCallback(_window, ManOnGrass::frameBufferSizeCB);
	glfwSetWindowUserPointer(_window, (void*)&_windowSize);
	return 1;
}

