#pragma once
#include <rapidxml.hpp>
#include<iostream>
#include<vector>
#include<string>
#include "Material.h"
#include"Texture.h"
#include "Viewer.h"
#include "Vec4f.h"
#include "Object.h"
#include "Mesh.h"

class Configuration
{

	const std::string rootNodeStr = "info";


private:

	Configuration();
	Configuration(std::string fileName);
	~Configuration() = default;
	void init();

	rapidxml::xml_document<> _configuration;
	std::vector<char> _buffer;
	rapidxml::xml_node<>* root_node = nullptr;


public:
	static Configuration& getIstance();
	Viewer getView();
	Object getObject();
	bool getMeshBG(Mesh& m);
	
	Texture getTextureBG();

	
	Material getMaterialBG();

	void applyUniforms(Material& mat);

	void applyUniforms(const std::string sceneName, Material& mat);




private:
	rapidxml::xml_node<>* getNode(rapidxml::xml_node<>* node, const std::string& tagName);
	rapidxml::xml_node<>* getNode(const std::string& tagName);
	bool getAttribute(rapidxml::xml_node<>* node, const std::string& tagName, std::string& str);
	bool getAttribute(rapidxml::xml_node<>* node, const std::string& tagName, int& value);
	bool getAttribute(rapidxml::xml_node<>* node, const std::string& tagName, bool& value);
	bool getAttribute(rapidxml::xml_node<>* node, const std::string& tagName, float& value);
	//bool getAttribute(rapidxml::xml_node<>* node, const std::string& tagName, Vec3f& value);
	bool getValue(rapidxml::xml_node<>* node, Vec4f& values);
	bool getValue(rapidxml::xml_node<>* node, std::vector<float>& values);
	bool getValue(rapidxml::xml_node<>* node, std::vector<int>& values);
	bool getValue(rapidxml::xml_node<>* node, std::vector<std::string>& values);

};
