#include "stdafx.h"
#include "CorrtexLight.h"
#include "GameEngine.h"


CorrtexLight::CorrtexLight():
	CorrtexLight(vec4(0,0,0,1), vec3(1))
{

}

CorrtexLight::CorrtexLight(vec4 pos, vec3 col)
{
	this->lightPosition = pos;
	this->lightColor = col;
	GameEngine::lightCount++;
	GameEngine::lights->Add(this);
}


CorrtexLight::~CorrtexLight()
{

}