#pragma once
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include<vector>
#include <string>

class Mesh
{


private:
	std::vector<GLfloat> _vertices;
	std::vector<GLuint> _indices;

	GLuint _VAO = -1; // SONO INT -> perché sono riferimenti
	GLuint _VBO = -1;
	GLuint _EBO = -1;

	unsigned int _vertex_mask = 0;
	unsigned int _stride = 0;

	bool hasPosition();
	bool hasNormal();
	bool hasColor();
	bool hasTexCoord();
	bool hasTangents();

	const unsigned int _mesh_vertices_position = 1;
	const unsigned int _mesh_vertices_texture_uv0 = 2;
	const unsigned int _mesh_vertices_color = 4;
	const unsigned int _mesh_vertices_normal = 8;
	const unsigned int _mesh_vertices_tangent = 16;

	const unsigned int _nElements_position = 3; // da quanti elementi è formata la posizione (x, y, z)
	const unsigned int _nElements_texCoord = 2;
	const unsigned int _nElements_color = 3;
	const unsigned int _nElements_normal = 3;
	const unsigned int _nElements_tangent = 3;


public:

	inline Mesh& operator=(const Mesh& m) {
		_vertices = m._vertices;
		_indices = m._indices;
		_vertex_mask = m._vertex_mask;
		_stride = m._stride;
		_VAO = m._VAO;
		_VBO = m._VBO;
		_EBO = m._EBO;
		return *this;
	}

	Mesh() {};
	~Mesh() {
		_vertices.clear();
		_indices.clear();
	};



	void setHasPositions(bool hasPos);
	void setHasTexCoords(bool hasTexCoord);
	void setHasVertexColor(bool hasVColor);
	void setHasNormals(bool hasNormals);
	void setHasTangents(bool hasTangents); //NEW NORMAL MAP

	unsigned int calculateStride();

	//void setMask(const std::string& element, bool isPresent);
	void setStride(unsigned int stride);

	void setVertices(std::vector<GLfloat> vertices);
	void setIndices(std::vector<GLuint> indices);
	std::vector<float> getVertices();

	std::vector<unsigned int> getIndices();


	unsigned int getStride();

	void draw();
	void initGL();

	void insertFace(GLuint v0, GLuint v1, GLuint v2); // da capire meglio
	void addToIndices(GLuint n);

	

private:


	void insertPosition(const float& x, const float& y, const float& z);
	void insertTexCoords(const float& u, const float& v);
	void insertColor(const float& r, const float& g, const float& b);
	void insertNormal(const float& x, const float& y, const float& z);
	void insertTangent(const float& x, const float& y, const float& z); // NEW NORMAL MAP
};