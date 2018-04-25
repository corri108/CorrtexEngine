#include "stdafx.h"
#include "CorrtexWater.h"
#include "GameEngine.h"

//ctor / dtor
CorrtexWater::CorrtexWater(vec3 pos)
{
	this->position = pos;
	this->name = "CorrtexWater Instance";
	GameEngine::LoadModel("Assets/water_plane.obj", this->vertices, this->uvs, this->normals);
	GameEngine::waterObject = this;

	this->waveStrength = 0.01f;
	this->waveSpeed = 0.041f;

	//larger waves values
	//strength: 0.01, speed : 0.041, uv : (3, 3)

	//smaller waves values
	//strength: 0.034000, speed: 0.090000, uv:(6.475080, 6.475080)
}
CorrtexWater::CorrtexWater() :
	CorrtexWater(vec3(0))
{

}
CorrtexWater::~CorrtexWater()
{
	glDeleteFramebuffers(1, &reflectionFrameBuffer);
	glDeleteFramebuffers(1, &refractionFrameBuffer);
	glDeleteTextures(1, &reflectionTexture);
	glDeleteTextures(1, &refractionTexture);
	glDeleteRenderbuffers(1, &reflectionDepthBuffer);
	glDeleteTextures(1, &refractionDepthTexture);
}

//generates special buffers
void CorrtexWater::GenSpecialBuffers()
{
	//generate frame buffer objects

	//reflection
	reflectionFrameBuffer = GameEngine::GenFrameBuffer();
	reflectionTexture = GameEngine::GenColorTexture(reflectionWidth, reflectionHeight);
	reflectionDepthBuffer = GameEngine::GenDepthBuffer(reflectionWidth, reflectionHeight);
	GameEngine::UnbindCurrentFrameBuffer();

	//refraction
	refractionFrameBuffer = GameEngine::GenFrameBuffer();
	refractionTexture = GameEngine::GenColorTexture(refractionWidth, refractionHeight);
	refractionDepthTexture = GameEngine::GenDepthTexture(refractionWidth, refractionHeight);
	GameEngine::UnbindCurrentFrameBuffer();
}

//update
void CorrtexWater::Update(float time)
{
	CorrtexObject::Update(time);

	waveTime += GameEngine::timeStep * waveSpeed;

	if (waveTime >= 1.0f)
	{
		waveTime -= 1.0f;
	}
}

//binds the current buffer to the reflection buffer
void CorrtexWater::BindReflectionFrameBuffer()
{
	GameEngine::BindFrameBuffer(this->reflectionFrameBuffer, this->reflectionWidth, this->reflectionHeight);
}

//binds the current buffer to the refraction buffer
void CorrtexWater::BindRefractionFrameBuffer()
{
	GameEngine::BindFrameBuffer(this->refractionFrameBuffer, this->refractionWidth, this->refractionHeight);
}
