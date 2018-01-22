#include "stdafx.h"
#include "CorrtexMesh.h"


CorrtexMesh::CorrtexMesh()
{
}

CorrtexMesh::CorrtexMesh(vec3 position, char *fileLoc)
{
	this->position = position;
	GameEngine::LoadModel(fileLoc, this->vertices, this->uvs, this->normals);
}

CorrtexMesh::~CorrtexMesh()
{
}

void CorrtexMesh::Initialize()
{
	//vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	//uv buffer
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec3), &uvs[0], GL_STATIC_DRAW);
	//normal buffer
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}


void CorrtexMesh::Draw(mat4 view, mat4 proj, ShaderUniform &mvpUniform)
{
	//calc model matrix and pass MVP to shader
	this->CalculateModelMatrix();
	mat4 mvp = proj * view * this->model;
	mvpUniform.SetValue(mvp);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	glDisableVertexAttribArray(0);
}
