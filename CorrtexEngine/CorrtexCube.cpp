#include "stdafx.h"
#include "CorrtexCube.h"
#include "SimpleUV.h"
#include "GameEngine.h"

CorrtexCube::CorrtexCube() :
	CorrtexCube(vec3(0), 1)
{

}

CorrtexCube::CorrtexCube(vec3 pos, float size)
{
	//transform / matrix stuff
	this->position = pos;
	this->startingPosition = pos;
	SetScaleUniform(size);
	this->startingScale = vec3(size);
	//vertex / drawing stuff
	this->vertexCount = 36;
	this->vertexBufferData = new GLfloat[this->vertexCount * 3]
	{
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,//one tri

		1, 0, 1,
		0, 0, 1,
		0, 0, 0,//two tri

		0, 0, 0,
		0, 1, 0,
		0, 1, 1,//three tri

		0, 1, 1,
		0, 0, 1,
		0, 0, 0,//four tri

		0, 1, 0,
		1, 1, 0,
		1, 1, 1,//5 tri

		1, 1, 1,
		0, 1, 1,
		0, 1, 0,//6 tri (half cube)

		0, 0, 0,
		1, 0, 0,
		1, 1, 0,

		1, 1, 0,
		0, 1, 0,
		0, 0, 0,

		0, 0, 1,
		1, 0, 1,
		1, 1, 1,

		1, 1, 1,
		0, 1, 1,
		0, 0, 1,

		1, 1, 1,
		1, 0, 1,
		1, 0, 0,

		1, 0, 0,
		1, 1, 0,
		1, 1, 1
	};
	this->colorBufferData = new GLfloat[this->vertexCount * 3]
	{
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,//one tri

		1, 0, 1,
		0, 0, 1,
		0, 0, 0,//two tri

		0, 0, 0,
		0, 1, 0,
		0, 1, 1,//three tri

		0, 1, 1,
		0, 0, 1,
		0, 0, 0,//four tri

		0, 1, 0,
		1, 1, 0,
		1, 1, 1,//5 tri

		1, 1, 1,
		0, 1, 1,
		0, 1, 0,//6 tri (half cube)

		0, 0, 0,
		1, 0, 0,
		1, 1, 0,

		1, 1, 0,
		0, 1, 0,
		0, 0, 0,

		0, 0, 1,
		1, 0, 1,
		1, 1, 1,

		1, 1, 1,
		0, 1, 1,
		0, 0, 1,

		1, 1, 1,
		1, 0, 1,
		1, 0, 0,

		1, 0, 0,
		1, 1, 0,
		1, 1, 1
	};
	this->name = "CorrtexCube Instance";
	this->UVBufferData = SimpleUV::GetCubeUVData();
	this->UVCoordCount = this->vertexCount;


	if (GameEngine::initLoaded)
	{
		//we need to initialize now instead of later
		this->Initialize();
	}
}

CorrtexCube::~CorrtexCube()
{

}