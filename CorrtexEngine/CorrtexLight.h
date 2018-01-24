#pragma once
#include "CorrtexCube.h"
using namespace glm;

class CorrtexLight : public CorrtexCube
{
public:
	CorrtexLight();
	CorrtexLight(vec4 pos, vec3 col);
	~CorrtexLight();
	virtual void Update(float time);
	vec4 lightPosition;
	vec3 lightColor;
	float attenuation = 0.1f;
	float coneAngle = 45.0f;
	vec3 coneDirection = vec3(0, -1, 0);
};

