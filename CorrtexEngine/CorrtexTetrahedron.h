#pragma once
#include "glew.h"
#include <glm/ext.hpp>
#include "CorrtexPrimitive.h"

class CorrtexTetrahedron : public CorrtexPrimitive
{
public:
	CorrtexTetrahedron();
	CorrtexTetrahedron(vec3 pos, float size);
	~CorrtexTetrahedron();
};

