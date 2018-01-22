#pragma once
#include "glew.h"
#include "glm/ext.hpp"

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
	Matrix4x4
};

class ShaderUniform
{
public:
	ShaderUniform(ShaderUniformType type, GLuint shaderProgram, char * glslName);
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
	void SetValue(int i1, int i2);
	void SetValue(int i1, int i2, int i3);
	void SetValue(int i1, int i2, int i3, int i4);
	//other
	void SetValue(GLuint texture);
	void SetValue(mat4 matrix);

	int GetHandle();

	GLuint shaderProgram;
	GLuint handle = 0;
	char* glslName = "";
	ShaderUniformType uniformType = Float1;
private:
	int GenerateLocationHandle();
};

