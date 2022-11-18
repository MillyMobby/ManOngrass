#pragma once
#include<string>
#include "Mesh.h"
//#include "Mat4f.h"

class Object
{
private:
	std::string _name;
	std::string _matName;
	bool _visible = true;
	bool _rotates = false;
	std::string _path;
	Mesh _mesh;
	//Mat4f _modelMatrix = Mat4f().identity();

public:
	Object() = default;
	~Object() {}

	void setName(const std::string& name);
	const std::string& getName() const;
	void setMatName(const std::string& matName);
	const std::string& getMatName() const;
	void setVisible(bool isVisible);
	bool isVisible();
	void setMesh(Mesh m);
	Mesh& getMesh();

	//Vec4f getPosition();

	//void setModelMatrix(Mat4f model);
	//Mat4f getModelMatrix() const; // NEW DA MODIFICARE reference

	const std::string getPath() const;
	void setPath(std::string path);

	void setRot(bool rotates);
	bool rotates();



	bool initGL();

	void draw();

};