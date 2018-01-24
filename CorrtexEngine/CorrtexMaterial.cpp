#include "stdafx.h"
#include "CorrtexMaterial.h"


CorrtexMaterial::CorrtexMaterial()
{
}

CorrtexMaterial::CorrtexMaterial(float ambient, float shininess, vec3 spec)
{
	this->ambientIntensity = ambient;
	this->shininess = shininess;
	this->specularColor = spec;
}


CorrtexMaterial::~CorrtexMaterial()
{
}
