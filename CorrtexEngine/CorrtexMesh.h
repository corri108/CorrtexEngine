#pragma once

#include "CorrtexObject.h"
#include <vector>

using namespace std;

//mesh class - this class is essentially an object that also has an array of verticies with specific attributes,
//creating a visual representation of a model.
class CorrtexMesh : public CorrtexObject
{
public:
	CorrtexMesh();
	CorrtexMesh(vec3 position, char *fileLoc);
	~CorrtexMesh();
	virtual void Draw(mat4 view, mat4 proj, ShaderUniform &mvpUniform);
	virtual void Initialize();
	virtual void AddTexture(char * textureLocation);
	void AddTexture(GLuint textureLoc);
	void SetShaderValues(mat4 mvp, mat4 view);
	virtual void SetShaderAttributes();
	virtual void ShaderInit();
	virtual void GenSpecialBuffers();

	//member variables
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals;
	vector<glm::vec3> tangents;
	vector<glm::vec3> bitangents;
	vector<unsigned short> indicies;

	//buffers that are needed
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