#pragma once
#include "CorrtexPrimitive.h"

//simple quad primitive
class CorrtexQuad : public CorrtexPrimitive
{
public:
	CorrtexQuad();
	CorrtexQuad(vec3 pos, float size);
	~CorrtexQuad();
	void Draw(mat4 view, mat4 proj, ShaderUniform &mvpUniform);
};

