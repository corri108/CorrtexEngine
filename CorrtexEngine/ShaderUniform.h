#pragma once
#include "glew.h"
#include "glm/ext.hpp"
#include <vector>

using namespace glm;

enum ShaderUniformType
{
	Float1,
	Float2,
	Float3,
	Float4,
	Int1,
	Int2,
	Int3,
	Int4,
	Texture,
	Matrix2x2,
	Matrix3x3,
	Matrix4x4
};

class ShaderUniform
{
public:
	ShaderUniform(ShaderUniformType type, GLuint shaderProgram, char * glslName);
	ShaderUniform(ShaderUniformType type, GLuint shaderProgram, char * arrayStructName, char* attribute);
	~ShaderUniform();
	//float
	void SetValue(float f1);
	void SetValue(float f1, float f2);
	void SetValue(vec2 f);
	void SetValue(float f1, float f2, float f3);
	void SetValue(vec3 f);
	void SetValue(float f1, float f2, float f3, float f4);
	void SetValue(vec4 f);
	//int
	void SetValuei(int i1, int i2);
	void SetValuei(int i1, int i2, int i3);
	void SetValuei(int i1, int i2, int i3, int i4);
	//other
	void SetValue(GLuint texture);
	void SetValue(GLuint texture, int texNum);
	void SetValue(mat4 matrix);
	void SetValuei(int vali);
	int GetHandle();

	//multiple
	bool valueInArray = false;
	void SetArrayValues();

	GLuint shaderProgram;
	GLuint handle = 0;
	std::vector<GLuint> handles;
	char* glslName = "";
	ShaderUniformType uniformType = Float1;
	char* arrayStructName = NULL;
	char* arrayStructAttribute = NULL;
private:
	int GenerateLocationHandle();
	std::vector<GLuint> GenerateLocationHandles();
	//for things that only get set once at the beginning
	bool setOnce = false;
};

