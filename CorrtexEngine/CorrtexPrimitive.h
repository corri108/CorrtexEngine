#pragma once
#include "CorrtexObject.h"

class CorrtexPrimitive : public CorrtexObject
{
public:
	CorrtexPrimitive();
	CorrtexPrimitive(vec3 pos, int vertexCount);
	~CorrtexPrimitive();
	virtual void Draw(mat4 view, mat4 proj, ShaderUniform &mvpUniform);
	virtual void Initialize();
	virtual void Initialize(GLfloat *vertData, GLfloat *colorData);
	virtual void SetBufferData();
	virtual void SetBufferData(GLfloat *vertData, GLfloat *colorData);
	virtual void CreateBuffers();
	virtual void Debug();
	int vertexCount = 9;//triangle
	void SetTexture(GLuint texture);
protected:
	GLfloat *vertexBufferData;
	GLfloat *colorBufferData;
	GLfloat *UVBufferData;
	GLuint vertexBuffer = 0;
	GLuint colorBuffer = 1;
	GLuint UVBuffer = 2;
	bool flicker = false;
	int flickerCount = 0;
	int UVCoordCount = 0;
	GLuint texture;
	bool useTexture = false;
};

