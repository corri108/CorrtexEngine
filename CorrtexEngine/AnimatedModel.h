#pragma once

#include "Joint.h"
#include "CorrtexMesh.h"

#ifndef ANIMATEDMODEL_H
#define ANIMATEDMODEL_H

class Animator;

class AnimatedModel : public CorrtexMesh
{
public:
	AnimatedModel(vec3 pos, const char *filePath);
	~AnimatedModel();
	virtual void SetShaderAttributes();
	virtual void GenSpecialBuffers();
	virtual void Initialize();
	virtual void Update(float time);
	mat4 * GetJointTransforms();
	void AddJoints(Joint *head, mat4* jointMatrices);

	//extra stuff for skin
	vector<glm::ivec3> jointIDs;
	GLuint jointIDBuffer;

	vector<glm::vec3> weights;
	GLuint weightBuffer;

	//skeleton
	int jointCount;
	Joint *root = NULL;
	Animator *animator = NULL;
};

#endif //ANIMATEDMODEL_H