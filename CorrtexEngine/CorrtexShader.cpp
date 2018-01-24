#include "stdafx.h"
#include "CorrtexShader.h"
#include "GameEngine.h"

CorrtexShader::CorrtexShader(char *vertexFile, char *fragmentFile)
{
	this->vertexShaderFileName = vertexFile;
	this->fragmentShaderFileName = fragmentFile;
	this->uniforms = new LinkedList<ShaderUniform*>();

	this->shaderID = GameEngine::LoadShaders(this->vertexShaderFileName, this->fragmentShaderFileName);
}

CorrtexShader::~CorrtexShader()
{

}

void CorrtexShader::AddUniform(ShaderUniform *uni)
{
	uniforms->Add(uni);
}

void CorrtexShader::AddUniform(ShaderUniformType type, char* glslName)
{
	uniforms->Add(new ShaderUniform(type, this->shaderID, glslName));
}
void CorrtexShader::AddUniforms(ShaderUniformType type1, char* glslName1, ShaderUniformType type2, char* glslName2)
{
	uniforms->Add(new ShaderUniform(type1, this->shaderID, glslName1));
	uniforms->Add(new ShaderUniform(type2, this->shaderID, glslName2));
}
void CorrtexShader::AddUniforms(ShaderUniformType type1, char* glslName1, ShaderUniformType type2, char* glslName2, ShaderUniformType type3, char* glslName3)
{
	uniforms->Add(new ShaderUniform(type1, this->shaderID, glslName1));
	uniforms->Add(new ShaderUniform(type2, this->shaderID, glslName2));
	uniforms->Add(new ShaderUniform(type3, this->shaderID, glslName3));
}

void CorrtexShader::AddUniformArray(ShaderUniformType type, char* structName, char* attribName)
{
	uniforms->Add(new ShaderUniform(type, this->shaderID, structName, attribName));
}
void CorrtexShader::AddUniformsArray(ShaderUniformType type1, char* structName1, char* attribName1, ShaderUniformType type2, char* structName2, char* attribName2)
{
	uniforms->Add(new ShaderUniform(type1, this->shaderID, structName1, attribName1));
	uniforms->Add(new ShaderUniform(type2, this->shaderID, structName2, attribName2));
}
void CorrtexShader::AddUniformsArray(ShaderUniformType type1, char* structName1, char* attribName1, ShaderUniformType type2, char* structName2, char* attribName2,
	ShaderUniformType type3, char* structName3, char* attribName3)
{
	uniforms->Add(new ShaderUniform(type1, this->shaderID, structName1, attribName1));
	uniforms->Add(new ShaderUniform(type2, this->shaderID, structName2, attribName2));
	uniforms->Add(new ShaderUniform(type3, this->shaderID, structName3, attribName3));
}

void CorrtexShader::AddAttribute(ShaderLayoutLocation layoutLocation)
{
	attributeList.push_back(layoutLocation);
}
void CorrtexShader::AddAttributes(ShaderLayoutLocation layoutLocation1, ShaderLayoutLocation layoutLocation2)
{
	attributeList.push_back(layoutLocation1);
	attributeList.push_back(layoutLocation2);
}
void CorrtexShader::AddAttributes(ShaderLayoutLocation layoutLocation1, ShaderLayoutLocation layoutLocation2, ShaderLayoutLocation layoutLocation3)
{
	attributeList.push_back(layoutLocation1);
	attributeList.push_back(layoutLocation2);
	attributeList.push_back(layoutLocation3);
}

bool CorrtexShader::HasAttribute(ShaderLayoutLocation att)
{
	int c = attributeList.size();

	for (int i = 0; i < c; ++i)
	{
		ShaderLayoutLocation attL = (attributeList[i]);

		if (attL == att)
			return true;
	}

	return false;
}

void CorrtexShader::UseShader()
{
	glUseProgram(shaderID);
}

LinkedList<ShaderUniform*> &CorrtexShader::GetUniforms()
{
	return *this->uniforms;
}
