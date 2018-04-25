#pragma once

#include <glm\ext.hpp>
using namespace glm;

//light class. this is used to place in a level in order to give it light. depending on the shader and material
//used on each object, the light will affect the level in different ways.
class CorrtexLight
{
public:
	CorrtexLight();
	CorrtexLight(vec4 pos, vec3 col);
	~CorrtexLight();
	vec4 lightPosition;
	vec3 lightColor;
	float attenuation = 0.1f;
	float coneAngle = 45.0f;
	vec3 coneDirection = vec3(0, -1, 0);
};

