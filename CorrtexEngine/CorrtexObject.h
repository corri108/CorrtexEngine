#pragma once

#include "glew.h"
#include <glm/ext.hpp>
#include "CorrtexShader.h"
#include "CorrtexDelegate.h"
#include "CorrtexMaterial.h"

using namespace glm;

//The base class for objects in the engine. 
class CorrtexObject
{
public:
	CorrtexObject();
	CorrtexObject(vec3 pos, char* name);
	~CorrtexObject();

	//overridable methods
	//purely virtual
	virtual void Initialize() = 0;
	virtual void ShaderInit() = 0;

	virtual void Update(float time);
	virtual void Draw(mat4 view, mat4 proj, ShaderUniform &mvpUniform);
	virtual void Debug();
	virtual void CalculateModelMatrix();
	virtual void SetShader(CorrtexShader *shader);
	virtual void SetShader(CorrtexShader &shader);
	virtual void SetMaterial(CorrtexMaterial *mat);
	virtual void SetMaterial(CorrtexMaterial &mat);

	//controls weather or not this object will be drawn when rendering the scene to a different buffer (like for water)
	bool renderOtherBuffers = true;

	//function pointer & behaviour so you can execute custom behaviors unique to different objects
	typedef void(CorrtexObject::*CorrtexBehaviour)(CorrtexObject);
	CorrtexBehaviour Behaviour = NULL;
	virtual void SetBehaviour(CorrtexBehaviour behaviour);

	//material for this object
	CorrtexMaterial *material = NULL;

	//transform & name variables
	vec3 position;
	vec3 startingPosition;
	vec3 scale;
	vec3 startingScale;
	void SetScaleUniform(float s);	//set uniform scale method
	char* name;
	float yaw = 0.0f;
	float pitch = 0.0f;
	float roll = 0.0f;
protected:
	void GetErrorIfExists();
	mat4 model;
	mat4 rotation;
	mat4 yawMatrix;
	mat4 pitchMatrix;
	mat4 rollMatrix;
	CorrtexShader *shader = NULL;
};

