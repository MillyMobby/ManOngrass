#include "Viewer.h"

void Viewer::setTitle(string t) {
	//samamammamama
	title = t;
}
void Viewer::setBGImage() {
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

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
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

	//texture("C:\\Users\\Martinelli PC\\Downloads\\erba.png");
	stbi_set_flip_vertically_on_load(true);
	_image = stbi_load("D: / grass.png", &width, &height, &_channels, 0);

	//init Textures
	if (_image) {
		std::cout << "numero canali: " << _channels << "path texture: " << "D: / grass.png" << std::endl;
		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, _channels > 3 ? GL_RGBA : GL_RGB, width, height, 0, _channels > 3 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, _image);
		glGenerateMipmap(GL_TEXTURE_2D);


	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(_image);
}
void Viewer::setBackgroundColor(float r, float g, float b, float a) {
	backgroundColor.x = r;
	backgroundColor.y = g;
	backgroundColor.z = b;
	backgroundColor.w = a;
}

void Viewer::setBackgroundColor(Vec4f vecColor) {

	backgroundColor = vecColor;
}

void Viewer::setWidth(int w) {
	width = w;
}

void Viewer::setHeight(int h) {
	height = h;
}

bool Viewer::Init() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	glfwMakeContextCurrent(_window);

	if (_window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return 0;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return 0;
	}

	bg.setName("background");
	bg.setVShader("D:/Man on grass/manOnGrass/manOnGrass/bg.vert");
	bg.setFShader("D:/Man on grass/manOnGrass/manOnGrass/bg.frag");
	std::cout << "path1 " << bg.getVShader();
	std::cout << "path2 " << bg.getFShader();

	setBGImage();
	bg.buildMaterial();
	std::cout << "path1 " << bg.getVShader();
	std::cout << "path2 " << bg.getFShader();
	bg.draw();
	//bg.setT1("tex1", 0);
	glUniform1i(glGetUniformLocation(bg.getShaderProgram(), "tex1"), 0);

	/*o.setName("sfondo");
	o.setMatName(bg.getName());
	o.initBG();*/

	/*s.setName("sprite");
	s.setMatName(bg.getName());
	s.initSprite();*/

	return 1;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Viewer::Run() {



	if (Init()) { // controlla se init ha dato errore

		while (!glfwWindowShouldClose(_window)) {
			processInput(_window);


			glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindTexture(GL_TEXTURE_2D, texture1);

			// render container
			glUseProgram(bg.getShaderProgram());
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glActiveTexture(GL_TEXTURE0);
			//bgT.bind();
			// glBindTexture(GL_TEXTURE_2D, 0);
			//glActiveTexture(GL_TEXTURE1);


			// render container
			//o.draw();
			//.drawSprite();
			//s.draw();
			/*glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/

			glfwSwapBuffers(_window);
			glfwPollEvents();
		}

		Clean();

	}
}

void Viewer::Clean() {

	glfwTerminate();
	_window = nullptr;

}