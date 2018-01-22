#include "stdafx.h"
#include "ShaderUniform.h"


ShaderUniform::ShaderUniform(ShaderUniformType type, GLuint shaderProgram, char * glslName)
{
	this->shaderProgram = shaderProgram;
	this->glslName = glslName;
	this->uniformType = type;

	this->handle = GenerateLocationHandle();
}

ShaderUniform::~ShaderUniform()
{

}

int ShaderUniform::GenerateLocationHandle()
{
	return glGetUniformLocation(shaderProgram, glslName);
}

int ShaderUniform::GetHandle()
{
	return handle;
}

//float
void ShaderUniform::SetValue(float f1)
{
	glUniform1f(this->handle, f1);
}
void ShaderUniform::SetValue(float f1, float f2)
{
	glUniform2f(this->handle, f1, f2);
}
void ShaderUniform::SetValue(vec2 f)
{
	glUniform2f(this->handle, f.x, f.y);
}
void ShaderUniform::SetValue(float f1, float f2, float f3)
{
	glUniform3f(this->handle, f1, f2, f3);
}
void ShaderUniform::SetValue(vec3 f)
{
	glUniform3f(this->handle, f.x, f.y, f.z);
}
void ShaderUniform::SetValue(float f1, float f2, float f3, float f4) 
{
	glUniform4f(this->handle, f1, f2, f3, f4);
}
void ShaderUniform::SetValue(vec4 f)
{
	glUniform4f(this->handle, f.x, f.y, f.z, f.w);
}
//int
void ShaderUniform::SetValue(int i1, int i2)
{
	glUniform2i(handle, i1, i2);
}
void ShaderUniform::SetValue(int i1, int i2, int i3) 
{
	glUniform3i(handle, i1, i2, i3);
}
void ShaderUniform::SetValue(int i1, int i2, int i3, int i4)
{
	glUniform4i(handle, i1, i2, i3, i4);
}
//other
void ShaderUniform::SetValue(GLuint texture)
{
	glUniform1i(handle, texture);
}
void ShaderUniform::SetValue(mat4 matrix)
{
	glUniformMatrix4fv(handle, 1, GL_FALSE, &matrix[0][0]);
}