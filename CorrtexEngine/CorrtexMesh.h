#pragma once

#include "CorrtexObject.h"
#include <vector>

using namespace std;

class CorrtexMesh : public CorrtexObject
{
public:
	#pragma message("CORRTEX MESH INCLUDED.")
	CorrtexMesh();
	CorrtexMesh(vec3 position, char *fileLoc);
	~CorrtexMesh();
	virtual void Draw(mat4 view, mat4 proj, ShaderUniform &mvpUniform);
	virtual void Initialize();
	virtual void AddTexture(char * textureLocation);
	void AddTexture(GLuint textureLoc);
	void SetShaderValues(mat4 mvp, mat4 view);
	void SetShaderAttributes();
	virtual void ShaderInit();
	virtual void GenSpecialBuffers();

	//member variables
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals;
	vector<glm::vec3> tangents;
	vector<glm::vec3> bitangents;
	vector<unsigned short> indicies;

	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint normalBuffer;
	GLuint tangentBuffer;
	GLuint bitangentBuffer;
	GLuint indexBuffer;
	GLuint texture;
	bool useTextures = false;
	bool useIndexing = true;
};