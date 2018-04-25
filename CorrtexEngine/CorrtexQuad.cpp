#include "stdafx.h"
#include "CorrtexQuad.h"


CorrtexQuad::CorrtexQuad() :
	CorrtexQuad(vec3(0), 1.0f)
{
}

CorrtexQuad::CorrtexQuad(vec3 pos, float size)
{
	//transform / matrix stuff
	this->position = pos;
	this->startingPosition = pos;
	SetScaleUniform(size);
	this->startingScale = vec3(size);
	//vertex / drawing stuff
	this->vertexCount = 4;
	this->vertexBufferData = new GLfloat[vertexCount * 3]
	{
		-50.0f, 0.0f, -50.0f,
		-50.0f, 0.0f, 50.0f,
		50.0f, 0.0f, 50.0f,
		50.0f, 0.0f, -50.0f
	};
	//GLfloat *originalVertexBufferData = new GLfloat[testVertexCount * 3];
	this->colorBufferData = new GLfloat[vertexCount * 3]
	{
		0.33f, 0.3f, 0.33f,
		0.3f, 0.33f, 0.3f,
		0.3f, 0.3f, 0.33f,
		0.33f, 0.33f, 0.3f
	};
	this->name = "CorrtexQuad Instance";
}


CorrtexQuad::~CorrtexQuad()
{

}

void CorrtexQuad::Draw(mat4 view, mat4 proj, ShaderUniform &mvpUniform)
{
	this->CalculateModelMatrix();
	mat4 mvp = proj * view * model;
	mvpUniform.SetValue(mvp);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_QUADS, 0, vertexCount);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}