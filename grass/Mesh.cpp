#include "Mesh.h"
#include<iostream>

void Mesh::setVertices(std::vector<GLfloat> vertices) {
    for (auto vertex : vertices) {
        _vertices.push_back(vertex);
    }
}

void Mesh::setIndices(std::vector<GLuint> indices) {
    for (auto vertex : indices) {
        _indices.push_back(vertex);
    }
}

std::vector<float> Mesh::getVertices() {
    return _vertices;
}

std::vector<unsigned int> Mesh::getIndices() { // non so se serve
    return _indices;
}

void Mesh::insertPosition(const float& x, const float& y, const float& z) { // NEW PER ASSIMP da vedere se va bene
    _vertices.push_back(x);
    _vertices.push_back(y);
    _vertices.push_back(z);
}

void Mesh::insertTexCoords(const float& u, const float& v) { // NEW PER ASSIMP da vedere se va bene
    _vertices.push_back(u);
    _vertices.push_back(v);
}

void Mesh::insertColor(const float& r, const float& g, const float& b) { // NEW PER ASSIMP da vedere se va bene
    _vertices.push_back(r);
    _vertices.push_back(g);
    _vertices.push_back(b);
}

void Mesh::insertNormal(const float& x, const float& y, const float& z) { // NEW PER ASSIMP da vedere se va bene
    _vertices.push_back(x);
    _vertices.push_back(y);
    _vertices.push_back(z);
}

void Mesh::insertTangent(const float& x, const float& y, const float& z) {
    _vertices.push_back(x);
    _vertices.push_back(y);
    _vertices.push_back(z);
}


void Mesh::insertFace(GLuint v0, GLuint v1, GLuint v2) { // ?????????????????? 
    _indices.push_back(v0);
    _indices.push_back(v1);
    _indices.push_back(v2);
}

void Mesh::addToIndices(GLuint n) { // NEW ASSIMP CREDO MOMENTANEA
    _indices.push_back(n);
}

void Mesh::setHasPositions(bool hasPos) {
    _vertex_mask = hasPos ? (_vertex_mask | _mesh_vertices_position) : (_vertex_mask & ~_mesh_vertices_position);
}

void Mesh::setHasTexCoords(bool hasTexCoord) {
    _vertex_mask = hasTexCoord ? (_vertex_mask | _mesh_vertices_texture_uv0) : (_vertex_mask & ~_mesh_vertices_texture_uv0);
}

void Mesh::setHasVertexColor(bool hasVColor) {
    _vertex_mask = hasVColor ? (_vertex_mask | _mesh_vertices_color) : (_vertex_mask & ~_mesh_vertices_color);
}

void Mesh::setHasNormals(bool hasNormals) {
    _vertex_mask = hasNormals ? (_vertex_mask | _mesh_vertices_normal) : (_vertex_mask & ~_mesh_vertices_normal);
}

void Mesh::setHasTangents(bool hasTangents) {
    _vertex_mask = hasTangents ? (_vertex_mask | _mesh_vertices_tangent) : (_vertex_mask & ~_mesh_vertices_tangent);
}


void Mesh::setStride(unsigned int stride) {
    _stride = stride;
}

unsigned int Mesh::getStride() {
    return _stride;
}


void Mesh::initGL() {

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    GLsizeiptr verticesSize = _vertices.size() * sizeof(_vertices[0]);


    glBufferData(GL_ARRAY_BUFFER, verticesSize, _vertices.data(), GL_STATIC_DRAW);

    GLsizeiptr indicesSize = _indices.size() * sizeof(_indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, _indices.data(), GL_STATIC_DRAW);

    _stride = calculateStride(); // per ora lo metto qui
    //unsigned int stride = calculateStride(); // non so se conviene calcolarlo subito o qui io per ora lo calcolo subito

    unsigned int position = 0;
    if (hasPosition()) {
        //std::cout << "POSIZIONE ";
        glVertexAttribPointer(0, _nElements_position, GL_FLOAT, GL_FALSE, _stride * sizeof(GLfloat), (GLvoid*)(position * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(0);
        position += _nElements_position;
    }
    if (hasTexCoord()) {
        //std::cout << "TEXTURE ";
        glVertexAttribPointer(1, _nElements_texCoord, GL_FLOAT, GL_FALSE, _stride * sizeof(GLfloat), (GLvoid*)(position * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(1);
        position += _nElements_texCoord;
    }
    if (hasColor()) {
        //std::cout << "COLOR ";
        glVertexAttribPointer(2, _nElements_color, GL_FLOAT, GL_FALSE, _stride * sizeof(GLfloat), (GLvoid*)(position * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(2);
        position += _nElements_color;
    }
    if (hasNormal()) {
        //std::cout << "NORMAL ";
        glVertexAttribPointer(3, _nElements_normal, GL_FLOAT, GL_FALSE, _stride * sizeof(GLfloat), (GLvoid*)(position * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(3);
        position += _nElements_normal;
    }
    if (hasTangents()) {
        glVertexAttribPointer(4, _nElements_tangent, GL_FLOAT, GL_FALSE, _stride * sizeof(GLfloat), (GLvoid*)(position * sizeof(GL_FLOAT)));
        glEnableVertexAttribArray(4);
        position += _nElements_tangent;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


unsigned int Mesh::calculateStride() {
    int stride = 0;
    if (hasPosition()) {
        stride += _nElements_position;
    }
    if (hasTexCoord()) {
        stride += _nElements_texCoord;
    }
    if (hasColor()) {
        stride += _nElements_color;
    }
    if (hasNormal()) {
        stride += _nElements_normal;
    }
    if (hasTangents()) {
        stride += _nElements_tangent;
    }
    return stride;
}

bool Mesh::hasPosition() {
    return _vertex_mask & _mesh_vertices_position;
}

bool Mesh::hasTexCoord() {
    return _vertex_mask & _mesh_vertices_texture_uv0;
}

bool Mesh::hasColor() {

    return _vertex_mask & _mesh_vertices_color;
}

bool Mesh::hasNormal() {
    return _vertex_mask & _mesh_vertices_normal;
}

bool Mesh::hasTangents() {
    return _vertex_mask & _mesh_vertices_tangent;
}



void Mesh::draw() {

    glBindVertexArray(_VAO);

    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0); // NEWW

}



