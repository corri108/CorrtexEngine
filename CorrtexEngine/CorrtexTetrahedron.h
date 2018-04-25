#pragma once
#include "glew.h"
#include <glm/ext.hpp>
#include "CorrtexPrimitive.h"

//simple tetrahedron primitive class
class CorrtexTetrahedron : public CorrtexPrimitive
{
public:
	CorrtexTetrahedron();
	CorrtexTetrahedron(vec3 pos, float size);
	~CorrtexTetrahedron();
};

