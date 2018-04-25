#pragma once

#include "glew.h"
#include <glm/ext.hpp>
#include "CorrtexPrimitive.h"

using namespace glm;

//basic cube primitive class - inherits from CorrtexPrimitive
class CorrtexCube : public CorrtexPrimitive
{
public:
	CorrtexCube();
	CorrtexCube(vec3 pos, float size);
	~CorrtexCube();
private:
};

