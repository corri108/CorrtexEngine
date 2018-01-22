#pragma once

#include "glew.h"
#include <glm/ext.hpp>
#include "ShaderUniform.h"
#include "CorrtexDelegate.h"

using namespace glm;

class CorrtexObject
{
public:
	CorrtexObject();
	CorrtexObject(vec3 pos, char* name);
	virtual void Update(float time);
	virtual void Draw(mat4 view, mat4 proj, ShaderUniform &mvpUniform);
	virtual void Initialize();
	virtual void Debug();
	virtual void CalculateModelMatrix();
	~CorrtexObject();
	typedef void(CorrtexObject::*CorrtexBehaviour)(CorrtexObject);
	CorrtexBehaviour Behaviour = NULL;
	virtual void SetBehaviour(CorrtexBehaviour behaviour);

	void SetScale(float s);

	vec3 position;
	vec3 startingPosition;
	vec3 scale;
	vec3 startingScale;
	char* name;
	float yaw = 0.0f;
	float pitch = 0.0f;
	float roll = 0.0f;

	mat4 yawMatrix;
	mat4 pitchMatrix;
	mat4 rollMatrix;
protected:
	void GetErrorIfExists();
	mat4 model;
	mat4 rotation;
};

