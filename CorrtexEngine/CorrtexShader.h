#pragma once
#include "glew.h"
#include "glm\ext.hpp"
#include "ShaderUniform.h"
#include "LinkedList.h"
#include <vector>

using namespace std;

//enum to categorize different layouts of vertex attributes
enum ShaderLayoutLocation
{
	VERTEX = 0,
	COLOR = 1,
	UV = 2,
	NORMAL = 3,
	TANGENT = 4,
	BITANGENT = 5,
	JOINTS = 6,
	WEIGHTS = 7
};

//shader class
class CorrtexShader
{
public:
	CorrtexShader(char *vertexFile, char *fragmentFile);
	~CorrtexShader();

	//important stuff
	GLuint shaderID;
	LinkedList<ShaderUniform*> *uniforms = NULL;
	std::vector <ShaderLayoutLocation> attributeList;
	char * vertexShaderFileName = "";
	char * fragmentShaderFileName = "";

	//adding uniforms and other methods
	LinkedList<ShaderUniform*> &GetUniforms();
	void AddUniform(ShaderUniform *uni);
	void AddUniform(ShaderUniformType type, char* glslName);
	void AddUniforms(ShaderUniformType type1, char* glslName1, ShaderUniformType type2, char* glslName2);
	void AddUniforms(ShaderUniformType type1, char* glslName1, ShaderUniformType type2, char* glslName2, ShaderUniformType type3, char* glslName3);

	void AddUniformArray(ShaderUniformType type, char* structName, char* attribName);
	void AddUniformsArray(ShaderUniformType type1, char* structName1, char* attribName1, ShaderUniformType type2, char* structName2, char* attribName2);
	void AddUniformsArray(ShaderUniformType type1, char* structName1, char* attribName1, ShaderUniformType type2, char* structName2, char* attribName2,
		ShaderUniformType type3, char* structName3, char* attribName3);

	void AddAttribute(ShaderLayoutLocation layoutLocation);
	void AddAttributes(ShaderLayoutLocation layoutLocation1, ShaderLayoutLocation layoutLocation2);
	void AddAttributes(ShaderLayoutLocation layoutLocation1, ShaderLayoutLocation layoutLocation2, ShaderLayoutLocation layoutLocation3);
	bool HasAttribute(ShaderLayoutLocation att);
	void UseShader();
};

