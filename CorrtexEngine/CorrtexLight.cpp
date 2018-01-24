#include "stdafx.h"
#include "CorrtexLight.h"


CorrtexLight::CorrtexLight():
	CorrtexLight(vec4(0,0,0,1), vec3(1))
{

}

CorrtexLight::CorrtexLight(vec4 pos, vec3 col)
{
	this->lightPosition = pos;
	this->lightColor = col;
	this->SetScale(0.05f);
}


CorrtexLight::~CorrtexLight()
{

}

void CorrtexLight::Update(float time)
{
	this->position = this->lightPosition;
}