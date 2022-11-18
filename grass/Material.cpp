#include "Material.h"
#include <sstream>
#include <fstream>
#include <cmath>
#define M_PI 3.14159265 // va preso dall'algebra relazionale

void Material::clean() { // non so se è giusta
    _objects.clear();
}


void Material::setName(std::string name) {
    _name = name;
    //std::cout << "il nome appena messo: " << getName();
}

std::string& Material::getName() {
    return _name;
}


void Material::setVShader(std::string pathvShader) {
    _vShader = pathvShader;
}


const std::string& Material::getVShader() {
    return _vShader;
}

void Material::setFShader(std::string pathfShader) {
    _fShader = pathfShader;
}

const std::string& Material::getFShader() {
    return _fShader;
}

GLuint Material::getShaderProgram() {
    return _shaderProgram;
}


void Material::setVec4(const std::string& name, const float& x, const float& y, const float& z, const float& w) {
    glUniform4f(glGetUniformLocation(_shaderProgram, name.c_str()), x, y, z, w);
}

void Material::setVec3(const std::string name, const float& x, const float& y, const float& z) { // NEW LUCI 
    glUniform3f(glGetUniformLocation(_shaderProgram, name.c_str()), x, y, z);
}


void Material::setI1(const std::string name, const bool& b) { // NEW LUCI NON USATA PERCHé USO QUELLA PER INT
    glUniform1i(glGetUniformLocation(_shaderProgram, name.c_str()), b);
}

void Material::setF(const std::string name, const float& f) { // NEWW
    glUniform1f(glGetUniformLocation(_shaderProgram, name.c_str()), f);
}



void Material::setVec4i(const std::string& name, const int& x, const int& y, const int& z, const int& w) {
    glUseProgram(_shaderProgram); // NEW
    glUniform4i(glGetUniformLocation(_shaderProgram, name.c_str()), x, y, z, w);
}


void Material::setT1(const std::string name, const int& n) {

    glUniform1i(glGetUniformLocation(_shaderProgram, name.c_str()), n);
}

//void Material::setMat4(const std::string& name, const Mat4f& value) {
//
//    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, GL_FALSE, value.m.data());
//
//}


void Material::setUniform(const std::string& name, std::vector<int> value, const int& count) {

    switch (count) {
    case -1:
        setUniform(name, value, value.size());
        break;

    case 1: //quindi è texture
        setT1(name, value[0]);
        break;

    case 4:
        setVec4i(name, value[0], value[1], value[2], value[3]);
        //std::cout << name << " " << value[0] << " " << value[1] << " " << value[2] << " " << value[3] << " " << count << std::endl;

        break;



    default:
        std::cout << "numero di parametri di in uniform sbagliato";
        break;

    }

}


void Material::setUniform(const std::string& name, std::vector<float> value, const int& count) {

    switch (count) {
    case -1:
        setUniform(name, value, value.size());
        break;

    case 4:
        setVec4(name, value[0], value[1], value[2], value[3]);


        break;


    default:
        std::cout << "numero di parametri di in uniform sbagliato"; break;

    }

}


bool Material::readShader(const std::string& path, std::string& shader) {
    bool rv = true;
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(path);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shader = shaderStream.str();
    }

    catch (std::ifstream::failure error) {
        rv = false;
        std::cout << "ERRORE DI APERTURA FILE DELLO SHADER ->" << shader; // AGGIUNGERE QUALE SHADER
    }
    return rv;

}

bool Material::buildMaterial()
{

    bool rv = true;

    std::ifstream f;


    glUseProgram(0); //lo metto perchè ignoro tutto ciò che è precedente, 

                     //tutte le chiamate opengl fatte qui non possono rischiare di riferirsi a un program vecchio (lo 0 è come se fosse "NULL")

    f.open(getVShader());
    bool vShaderExist = f.good();
    f.close();

    f.open(getFShader());
    bool fShaderExist = f.good();
    f.close();


    if (vShaderExist && fShaderExist) {

        rv = buildMaterial(getVShader(), getFShader());
    }
    else {
        std::cout << "NON ESISTONO GLI SHADER DI " << _name << std::endl;
        rv = false;
    }


    return rv;
}


bool Material::buildMaterial(const std::string& vShaderPath, const std::string& fShaderPath)
{
    bool rv = false;
    if (readShader(vShaderPath, _vShader) && readShader(fShaderPath, _fShader)) {
        GLuint vShader;
        GLuint fShader;
        if (compile(getVShader(), GL_VERTEX_SHADER, vShader) && compile(getFShader(), GL_FRAGMENT_SHADER, fShader)) {
            if (link(vShader, fShader)) {

                glUseProgram(_shaderProgram); // momentaneo
                glDeleteShader(vShader);
                glDeleteShader(fShader);
                rv = true;
            }
        }
    }
    return rv;
}


bool Material::compile(const std::string& shaderCode, const GLenum& shaderType, GLuint& shader) {
    bool rv = true;
    const GLchar* shaderCodeChar = shaderCode.c_str();

    GLchar infoLog[512];
    GLint success;

    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCodeChar, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl; // non è solo fragment, quello è da cambiare
        rv = false;
    }
    return rv;
}


bool Material::link(const GLuint& vShader, const GLuint& fShader) {
    bool rv = true;

    GLchar infoLog[512];
    GLint success;

    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, vShader);
    glAttachShader(_shaderProgram, fShader);
    glLinkProgram(_shaderProgram);

    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        rv = false;
    }
    return rv;
}


void Material::draw() {
    glUseProgram(_shaderProgram);
}



void Material::addObject(std::string name, std::unordered_map<std::string, Object> objList) {
    _objects.push_back(name);
}


void Material::removeObject(std::string name, std::unordered_map<std::string, Object> objList) {
    for (int i = 0; i < _objects.size(); i++) {
        if (_objects[i] == name) {
            _objects.erase(_objects.begin() + i);
        }
    }
}


const std::vector<std::string>& Material::getObjects() const {
    return _objects;
}



void Material::addTexture(std::string textureName, int textureUnit) {//NEW TEXTURE
    //std::cout << "ADD TEXTURE" << textureName << " " << textureUnit << std::endl;
    _texturesUnit.insert(HashTextureUnitPair(textureName, textureUnit));

}

const Material::HashTextureUnit& Material::getTexturesUnit() const { //NEW TEXTURE
    return _texturesUnit;
}
