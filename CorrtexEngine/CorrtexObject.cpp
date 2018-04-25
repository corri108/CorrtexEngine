#include "stdafx.h"
#include "CorrtexObject.h"
#include "GameEngine.h"

//ctor / dtor
CorrtexObject::CorrtexObject() :
	CorrtexObject(vec3(0), "CorrtexObject Instance")
{
	
}
CorrtexObject::CorrtexObject(vec3 pos, char* name)
{
	this->position = pos;
	this->startingPosition = pos;
	this->scale = vec3(1.0f);
	this->startingScale = vec3(1.0f);
	this->yaw = 0.0f;
	this->pitch = 0.0f;
	this->roll = 0.0f;
	this->name = name;
	GameEngine::objectList->Add(this);
}
CorrtexObject::~CorrtexObject()
{

}

//set shaders & materials
void CorrtexObject::SetShader(CorrtexShader *shader)
{
	this->shader = shader;
	ShaderInit();
}
void CorrtexObject::SetShader(CorrtexShader &shader)
{
	this->shader = &shader;
	ShaderInit();
}
void CorrtexObject::SetMaterial(CorrtexMaterial *mat)
{
	this->material = mat;
}
void CorrtexObject::SetMaterial(CorrtexMaterial &mat)
{
	this->material = &mat;
}

//gets and prints a GLError if it exists
void CorrtexObject::GetErrorIfExists()
{
	GLenum err = glGetError();

	if (err != GLEW_OK)
	{
		char * errS = (char*)glewGetErrorString(err);
		printf("\nGL ERROR: %s\n\n", errS);
	}
}

//sets the behaviour function for this object
void CorrtexObject::SetBehaviour(CorrtexBehaviour behaviour)
{
	Behaviour = behaviour;
}

//calculates the model matrix for this object
void CorrtexObject::CalculateModelMatrix()
{
	this->yawMatrix = glm::rotate(yawMatrix, this->yaw, vec3(0.0f, 1.0f, 0.0f));
	this->pitchMatrix = glm::rotate(pitchMatrix, this->pitch, vec3(1.0f, 0.0f, 0.0f));
	this->rollMatrix = glm::rotate(rollMatrix, this->roll, vec3(0.0f, 0.0f, 1.0f));

	this->rotation = yawMatrix * pitchMatrix * rollMatrix;

	model = glm::translate(this->position) *
		this->rotation *
		glm::scale(this->scale);
}

//draws this object
void CorrtexObject::Draw(mat4 view, mat4 proj, ShaderUniform &mvpUniform)
{
	CalculateModelMatrix();
}

//updates this object
void CorrtexObject::Update(float time)
{
	if (Behaviour != NULL)
	{
		(*this.*Behaviour)(*this);
	}
}

//debug method
void CorrtexObject::Debug()
{
	printf("Name: %s, Pos: (%f, %f, %f) Rot: (%f) Scale: (%f, %f, %f)\n",
		name, position.x, position.y, position.z, rotation, scale.x, scale.y, scale.z);
}

//sets the uniform scale of this object
void CorrtexObject::SetScaleUniform(float s)
{
	this->scale = vec3(s);
}