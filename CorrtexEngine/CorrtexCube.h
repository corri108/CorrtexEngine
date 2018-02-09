#pragma once

#include "glew.h"
#include <glm/ext.hpp>
#include "CorrtexPrimitive.h"

using namespace glm;

class CorrtexCube : public CorrtexPrimitive
{
public:
	CorrtexCube();
	CorrtexCube(vec3 pos, float size);
	//virtual void Update(float time);
	~CorrtexCube();
	//virtual void Draw(mat4 view, mat4 proj, ShaderUniform &mvpUniform);
private:
};

