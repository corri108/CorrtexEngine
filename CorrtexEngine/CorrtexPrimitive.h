#pragma once
#include "CorrtexObject.h"

//primitive class - these objects are built in to the engine and drawn and constructed there,
//instead of using an outside model file.

class CorrtexPrimitive : public CorrtexObject
{
public:
	CorrtexPrimitive();
	CorrtexPrimitive(vec3 pos, int vertexCount);
	~CorrtexPrimitive();

	//must override the draw, initialize functions from CorrtexObject since we are creating the mesh by hand
	virtual void Draw(mat4 view, mat4 proj, ShaderUniform &mvpUniform);
	virtual void Initialize();
	virtual void Initialize(GLfloat *vertData, GLfloat *colorData);
	virtual void SetBufferData();
	virtual void SetBufferData(GLfloat *vertData, GLfloat *colorData);
	virtual void CreateBuffers();
	virtual void Debug();
	int vertexCount = 9;//triangle default - vertex count is actually (v * 3)
	void AddTexture(char *filePath);
	void CorrtexPrimitive::AddTexture(GLuint tex);
protected:
	//keep all of the buffers and data arrays here so we can modify them when we inherit to form specific primitives
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

