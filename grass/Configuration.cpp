#include "Configuration.h"
#include <fstream>
#include <sstream>
Configuration::Configuration() {

}

Configuration& Configuration::getIstance() {
	static Configuration istance;
	return istance;
}


void Configuration::init() {

	Viewer v = getView();
	/*Material bg = getMaterialBG();
	
	Texture bgT = getTextureBG();
	bgT.initGL();
	bg.buildMaterial();
	bg.setT1(bgT.getName(), 0);
	Object sfondo = getObject();
	sfondo.initGL();
	glActiveTexture(GL_TEXTURE0);
	T.bind();*/

}






Viewer Configuration::getView() {



	Viewer v;
	std::string title = "man on grass";

	int attrInt = 0;

	Vec4f backgroundColor = Vec4f(1, 0, 0, 1);

	v.setTitle(title);
	v.setWidth(800);
	v.setHeight(400);
	v.setBackgroundColor(backgroundColor);


	return v;
}





Material Configuration::getMaterialBG() {
	Material m;
	m.setName("bg"); 
	m.setVShader("D:/Man on grass/manOnGrass/manOnGrass/bg.vert");
	m.setFShader("D:/Man on grass/manOnGrass/manOnGrass/bg.frag");

	return m;
}



bool Configuration::getMeshBG(Mesh& m) {
	bool control = false;
	rapidxml::xml_node<>* meshNode;
	bool boolAttr;
	int intAttr;
	std::vector<GLfloat> verticesBG = {
		1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right  // top right
		1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	   -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	   -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left    // top left 
	};
	std::vector<GLuint> indicesBG = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

		m.setHasPositions(true); 
		m.setHasTexCoords(true); 

	    m.setVertices(verticesBG);
		m.setIndices(indicesBG);
			
	

	return control;

}




void Configuration::applyUniforms(Material& mat) {

	
				
					std::vector<int> _values;
					int value;
					
						_values.push_back(0);
						mat.setUniform("BG", _values, 1);
						mat.addTexture("BG", _values[0]);
				
	
}





Texture Configuration::getTextureBG() {

	Texture t;

	t.setName("tex1");
	t.setType("GL_TEXTURE_2D");
	t.setTexName("bgg");
	t.setImagePath("D:/grass.png");  // NON SERVOIRà PIù
	t.setMinFilter("GL_LINEAR");
	t.setMagFilter("GL_LINEAR");
	t.setWrapS("GL_CLAMP_TO_EDGE");
	t.setWrapT("GL_CLAMP_TO_EDGE");
	t.setWrapR("GL_CLAMP_TO_EDGE");

	

	//t.loadImages(); // DA ELIMINARE
	return t;

}

