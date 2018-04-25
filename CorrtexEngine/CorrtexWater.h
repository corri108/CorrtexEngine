#pragma once
#include "CorrtexMesh.h"

//class that handles the creation and drawing of the water - but not the actual water mesh!
class CorrtexWater : public CorrtexMesh
{
public:
	CorrtexWater();
	CorrtexWater(vec3 pos);
	~CorrtexWater();

	//generates special buffers needed for water
	virtual void GenSpecialBuffers();
	virtual void Update(float time);
	void BindReflectionFrameBuffer();
	void BindRefractionFrameBuffer();

	//locations of needed buffers and textures for reflection
	GLuint reflectionFrameBuffer;
	GLuint reflectionTexture;
	GLuint reflectionDepthBuffer;
	//locations of needed buffers and textures for refraction
	GLuint refractionFrameBuffer;
	GLuint refractionTexture;
	GLuint refractionDepthTexture;
	//wave speed strength and time
	float waveSpeed = 0.2f;
	float waveStrength = 10.0f;
	float waveTime = 0.0f;
	//width and height of the textures
	int reflectionWidth = 1280;
	int reflectionHeight = 720;
	int refractionWidth = 1280;
	int refractionHeight = 720;
};

