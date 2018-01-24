#pragma once
#include "CorrtexCube.h"
using namespace glm;

class CorrtexLight : public CorrtexCube
{
public:
	CorrtexLight();
	CorrtexLight(vec3 pos, vec3 col);
	~CorrtexLight();
	virtual void Update(float time);
	vec3 lightPosition;
	vec3 lightColor;
	float attenuation = 0.1f;
};

