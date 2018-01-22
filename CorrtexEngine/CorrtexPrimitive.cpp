#include "stdafx.h"
#include "CorrtexPrimitive.h"

CorrtexPrimitive::CorrtexPrimitive() : 
	CorrtexPrimitive(vec3(0), 3)
{
	
}

CorrtexPrimitive::CorrtexPrimitive(vec3 pos, int vCount)
{
	this->name = "CorrtexPrimitive Instance";
	this->position = pos;
	this->startingPosition = pos;
	this->vertexCount = vCount;
}

CorrtexPrimitive::~CorrtexPrimitive()
{
	delete this->vertexBufferData;
	delete this->colorBufferData;
}

void CorrtexPrimitive::SetBufferData()
{
	SetBufferData(this->vertexBufferData, this->colorBufferData);
}

void CorrtexPrimitive::SetBufferData(GLfloat *vertData, GLfloat *colorData)
{
	this->vertexBufferData = vertData;
	this->colorBufferData = colorData;

	//int i = 0;
	//int c = this->vertexCount * 3;

	//while (i < c)
	//{
	//	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	//	this->colorBufferData[i] = 0.6f;
	//	++i;
	//}
}

void CorrtexPrimitive::CreateBuffers()
{
	//generate vertex buffer first
	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertexCount * sizeof(GLfloat) * 3, this->vertexBufferData, GL_STATIC_DRAW);

	//now color buffer
	glGenBuffers(1, &this->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertexCount * sizeof(GLfloat) * 3, this->colorBufferData, GL_STATIC_DRAW);

	//lets change it up with a UV buffer!
	glGenBuffers(1, &this->UVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->UVBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->UVCoordCount * 2 * sizeof(GLfloat), this->UVBufferData, GL_STATIC_DRAW);
}

void CorrtexPrimitive::Debug()
{
	printf("Name: %s, Pos: (%f, %f, %f) CB[0]: %f\n",
		name, position.x, position.y, position.z, this->colorBufferData[3]);
}

void CorrtexPrimitive::Initialize()
{
	this->SetBufferData();
	this->CreateBuffers();
}

void CorrtexPrimitive::Initialize(GLfloat *vertData, GLfloat *colorData)
{
	this->SetBufferData(vertData, colorData);
	this->CreateBuffers();
}

void CorrtexPrimitive::SetTexture(GLuint texture)
{
	this->texture = texture;
	this->useTexture = true;
}

void CorrtexPrimitive::Draw(mat4 view, mat4 proj, ShaderUniform &mvpUniform)
{
	//calculate model matrix
	this->CalculateModelMatrix();

	//calculate model view proj matrix
	mat4 mvp = proj * view * model;

	//apply shader uniforms
	mvpUniform.SetValue(mvp);

	//vertex positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, this->vertexCount * sizeof(GLfloat) * 3, this->vertexBufferData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//color positions
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, this->vertexCount * sizeof(GLfloat) * 3, this->colorBufferData, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//UV coords
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, this->UVBuffer);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//if different texture
	if (this->useTexture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->texture);
	}

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 0; 3 vertices / triangle, 12 triangles total -> 12 * 3 vertices
										   //disable attributes after drawing
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}