#pragma once
#include "CorrtexMesh.h"

class CorrtexWater : public CorrtexMesh
{
public:
	//#pragma message("CORRTEX WATER INCLUDED.")
	CorrtexWater();
	CorrtexWater(vec3 pos);
	~CorrtexWater();
	virtual void GenSpecialBuffers();
	virtual void Update(float time);
	void BindReflectionFrameBuffer();
	void BindRefractionFrameBuffer();

	GLuint reflectionFrameBuffer;
	GLuint reflectionTexture;
	GLuint reflectionDepthBuffer;

	GLuint refractionFrameBuffer;
	GLuint refractionTexture;
	GLuint refractionDepthTexture;

	float waveSpeed = 0.2f;
	float waveStrength = 10.0f;
	float waveTime = 0.0f;

	int reflectionWidth = 1280;
	int reflectionHeight = 720;
	int refractionWidth = 1280;
	int refractionHeight = 720;
};

