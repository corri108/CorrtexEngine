#include "stdafx.h"
#include "CorrtexLight.h"


CorrtexLight::CorrtexLight():
	CorrtexLight(vec3(0), vec3(1))
{

}

CorrtexLight::CorrtexLight(vec3 pos, vec3 col)
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