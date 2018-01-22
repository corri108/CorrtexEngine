#include "stdafx.h"
#include "CorrtexTetrahedron.h"


CorrtexTetrahedron::CorrtexTetrahedron() :
	CorrtexTetrahedron::CorrtexTetrahedron(vec3(0), 1.0f)
{

}

CorrtexTetrahedron::CorrtexTetrahedron(vec3 pos, float size)
{
	//transform / matrix stuff
	this->position = pos;
	this->startingPosition = pos;
	SetScale(size);
	this->startingScale = vec3(size);
	//vertex / drawing stuff
	this->vertexCount = 12;
	this->vertexBufferData = new GLfloat[this->vertexCount * 3]
	{
		0,0, 0.35f,//1
		-0.5f, 0, -0.5f,//2
		0.5f, 0, -0.5f,//3

		0,0.5f, -0.2125f,//4
		-0.5f, 0, -0.5f,//2
		0.5f, 0, -0.5f,//3

		0,0.5f, -0.2125f,//4
		0,0, 0.35f,//1
		0.5f, 0, -0.5f,//3

		0,0.5f, -0.2125f,//4
		0,0, 0.35f,//1
		-0.5f, 0, -0.5f//2
	};
	this->colorBufferData = new GLfloat[this->vertexCount * 3]
	{
		0, 0, 0.5f,
		0.5f, 0, 0.5f,
		0.5f, 0, 0.5f,

		0, 0, 0.5f,
		0.5f, 0, 0.5f,
		0.5f, 0, 0.5f,

		0, 0, 0.5f,
		0.5f, 0, 0.5f,
		0.5f, 0, 0.5f,

		0, 0, 0.5f,
		0.5f, 0, 0.5f,
		0.5f, 0, 0.5f
	};
	this->name = "CorrtexTetrahedron Instance";
	this->UVBufferData = NULL;
	this->UVCoordCount = 0;
}


CorrtexTetrahedron::~CorrtexTetrahedron()
{
}
