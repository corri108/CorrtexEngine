#pragma once
#include "glew.h"
#include <glm/ext.hpp>
#include "CorrtexPrimitive.h"
#include "GameEngine.h"
#include <vector>
using namespace std;

class CorrtexMesh : public CorrtexObject
{
public:
	CorrtexMesh();
	CorrtexMesh(vec3 position, char *fileLoc);
	~CorrtexMesh();
	virtual void Draw(mat4 view, mat4 proj, ShaderUniform &mvpUniform);
	virtual void Initialize();
	vector< glm::vec3 > vertices;
	vector< glm::vec2 > uvs;
	vector< glm::vec3 > normals;
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint normalBuffer;
};

