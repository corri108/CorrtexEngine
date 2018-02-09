#include "stdafx.h"
#include "ShaderUniform.h"
#include "GameEngine.h"

ShaderUniform::ShaderUniform(ShaderUniformType type, GLuint shaderProgram, char * glslName)
{
	this->shaderProgram = shaderProgram;
	this->glslName = glslName;
	this->uniformType = type;

	this->handle = GenerateLocationHandle();
}

ShaderUniform::ShaderUniform(ShaderUniformType type, GLuint shaderProgram, char * arrayStructName, char* attribute)
{
	this->shaderProgram = shaderProgram;
	this->glslName = arrayStructName;
	this->uniformType = type;
	this->valueInArray = true;
	this->arrayStructName = arrayStructName;
	this->arrayStructAttribute = attribute;
	this->handles = GenerateLocationHandles();
}

ShaderUniform::~ShaderUniform()
{

}

int ShaderUniform::GenerateLocationHandle()
{
	return glGetUniformLocation(shaderProgram, glslName);
}

std::vector<GLuint> ShaderUniform::GenerateLocationHandles()
{
	std::vector<GLuint> genHandles;
	int numHandles = 1;

	if (this->arrayStructName == "allLights")
	{
		numHandles = GameEngine::lightCount;
	}

	for (int i = 0; i < numHandles; ++i)
	{
		char fullStructAttributeName[100];
		sprintf(fullStructAttributeName, "%s[%d].%s",this->arrayStructName, i, this->arrayStructAttribute);
		GLuint newHandle = glGetUniformLocation(shaderProgram, fullStructAttributeName);
		printf("buffer (loc, name): (%d, %s)\n", newHandle, fullStructAttributeName);
		genHandles.push_back(newHandle);
	}

	return genHandles;
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
void ShaderUniform::SetValuei(int i1, int i2)
{
	glUniform2i(handle, i1, i2);
}
void ShaderUniform::SetValuei(int i1, int i2, int i3) 
{
	glUniform3i(handle, i1, i2, i3);
}
void ShaderUniform::SetValuei(int i1, int i2, int i3, int i4)
{
	glUniform4i(handle, i1, i2, i3, i4);
}
//other
void ShaderUniform::SetValuei(int intVal)
{
	glUniform1i(handle, intVal);
}
void ShaderUniform::SetValue(GLuint texture)
{
	glUniform1i(handle, texture);
}
void ShaderUniform::SetValue(GLuint texture, int texNum)
{
	//this should only need to be set once
	//if (setOnce)
		//return;

	glUniform1i(handle, texNum);
	setOnce = true;
}
void ShaderUniform::SetValue(mat4 matrix)
{
	glUniformMatrix4fv(handle, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderUniform::SetArrayValues()
{
	int count = this->handles.size();

	for (int i = 0; i < count; ++i)
	{
		this->handle = this->handles[i];

		if (arrayStructAttribute == "pos")
		{
			SetValue(GameEngine::lights->Get(i)->lightPosition);
		}
		else if (arrayStructAttribute == "color")
		{
			SetValue(GameEngine::lights->Get(i)->lightColor);
		}
		else if (arrayStructAttribute == "attenuation")
		{
			SetValue(GameEngine::lights->Get(i)->attenuation);
		}
		else if (arrayStructAttribute == "coneAngle")
		{
			SetValue(GameEngine::lights->Get(i)->coneAngle);
		}
		else if (arrayStructAttribute == "coneDirection")
		{
			SetValue(GameEngine::lights->Get(i)->coneDirection);
		}
	}
}