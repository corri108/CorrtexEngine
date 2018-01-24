#pragma once
#include "glew.h"
#include "glm\ext.hpp"
using namespace glm;

class CorrtexMaterial
{
public:
	CorrtexMaterial();
	CorrtexMaterial(float ambient, float shininess, vec3 spec);
	~CorrtexMaterial();
	float ambientIntensity = 0.075f;
	float shininess = 0.1f;
	vec3 specularColor = vec3(0.22f, 0.12f, 0.35f);
};

